/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2012 Stephen Kelly <steveire@gmail.com>

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmGeneratorExpressionEvaluator_h
#define cmGeneratorExpressionEvaluator_h

#include <vector>
#include <string>

#include "cmListFileCache.h"

class cmTarget;
class cmGeneratorTarget;

//----------------------------------------------------------------------------
struct cmGeneratorExpressionContext
{
  cmListFileBacktrace Backtrace;
  std::set<cmTarget*> Targets;
  cmMakefile *Makefile;
  const char *Config;
  cmGeneratorTarget *Target;
  bool Quiet;
  bool HadError;
};

struct cmGeneratorExpressionDAGChecker;

//----------------------------------------------------------------------------
struct cmGeneratorExpressionEvaluator
{
  cmGeneratorExpressionEvaluator() {}
  virtual ~cmGeneratorExpressionEvaluator() {}

  enum Type
  {
    Text,
    Generator
  };

  virtual Type GetType() const = 0;

  virtual std::string Evaluate(cmGeneratorExpressionContext *context,
                              cmGeneratorExpressionDAGChecker *) const = 0;

private:
  cmGeneratorExpressionEvaluator(const cmGeneratorExpressionEvaluator &);
  void operator=(const cmGeneratorExpressionEvaluator &);
};

struct TextContent : public cmGeneratorExpressionEvaluator
{
  TextContent(const char *start, unsigned int length)
    : Content(start), Length(length)
  {

  }

  std::string Evaluate(cmGeneratorExpressionContext *,
                       cmGeneratorExpressionDAGChecker *) const
  {
    return std::string(this->Content, this->Length);
  }

  Type GetType() const
  {
    return cmGeneratorExpressionEvaluator::Text;
  }

  void Extend(unsigned int length)
  {
    this->Length += length;
  }

  unsigned int GetLength()
  {
    return this->Length;
  }

private:
  const char *Content;
  unsigned int Length;
};

//----------------------------------------------------------------------------
struct GeneratorExpressionContent : public cmGeneratorExpressionEvaluator
{
  GeneratorExpressionContent(const char *startContent, unsigned int length);
  void SetIdentifier(std::vector<cmGeneratorExpressionEvaluator*> identifier)
  {
    this->IdentifierChildren = identifier;
  }

  void SetParameters(
        std::vector<std::vector<cmGeneratorExpressionEvaluator*> > parameters)
  {
    this->ParamChildren = parameters;
  }

  Type GetType() const
  {
    return cmGeneratorExpressionEvaluator::Generator;
  }

  std::string Evaluate(cmGeneratorExpressionContext *context,
                       cmGeneratorExpressionDAGChecker *) const;

  std::string GetOriginalExpression() const;

  ~GeneratorExpressionContent();

private:
  std::vector<cmGeneratorExpressionEvaluator*> IdentifierChildren;
  std::vector<std::vector<cmGeneratorExpressionEvaluator*> > ParamChildren;
  const char *StartContent;
  unsigned int ContentLength;
};

#endif
