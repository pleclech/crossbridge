/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/

#ifndef cmGeneratorExpression_h
#define cmGeneratorExpression_h

#include "cmStandardIncludes.h"

#include <stack>

#include <cmsys/RegularExpression.hxx>

class cmTarget;
class cmGeneratorTarget;
class cmMakefile;
class cmListFileBacktrace;

struct cmGeneratorExpressionEvaluator;
struct cmGeneratorExpressionDAGChecker;

class cmCompiledGeneratorExpression;

/** \class cmGeneratorExpression
 * \brief Evaluate generate-time query expression syntax.
 *
 * cmGeneratorExpression instances are used by build system generator
 * implementations to evaluate the $<> generator expression syntax.
 * Generator expressions are evaluated just before the generate step
 * writes strings into the build system.  They have knowledge of the
 * build configuration which is not available at configure time.
 */
class cmGeneratorExpression
{
public:
  /** Construct. */
  cmGeneratorExpression(cmListFileBacktrace const& backtrace);
  ~cmGeneratorExpression();

  const cmCompiledGeneratorExpression& Parse(std::string const& input);
  const cmCompiledGeneratorExpression& Parse(const char* input);

  enum PreprocessContext {
    StripAllGeneratorExpressions
  };

  static std::string Preprocess(const std::string &input,
                                PreprocessContext context);

private:
  cmGeneratorExpression(const cmGeneratorExpression &);
  void operator=(const cmGeneratorExpression &);

  cmListFileBacktrace const& Backtrace;
  cmCompiledGeneratorExpression *CompiledExpression;
};

class cmCompiledGeneratorExpression
{
public:
  const char* Evaluate(cmMakefile* mf, const char* config,
                       bool quiet = false,
                       cmGeneratorTarget *target = 0,
                       cmGeneratorExpressionDAGChecker *dagChecker = 0) const;

  /** Get set of targets found during evaluations.  */
  std::set<cmTarget*> const& GetTargets() const
    { return this->Targets; }

  ~cmCompiledGeneratorExpression();

private:
  cmCompiledGeneratorExpression(cmListFileBacktrace const& backtrace,
              const std::vector<cmGeneratorExpressionEvaluator*> &evaluators,
              const char *input, bool needsParsing);

  friend class cmGeneratorExpression;

  cmCompiledGeneratorExpression(const cmCompiledGeneratorExpression &);
  void operator=(const cmCompiledGeneratorExpression &);

  cmListFileBacktrace const& Backtrace;
  const std::vector<cmGeneratorExpressionEvaluator*> Evaluators;
  const char* const Input;
  const bool NeedsParsing;

  mutable std::set<cmTarget*> Targets;
  mutable std::string Output;
};

#endif
