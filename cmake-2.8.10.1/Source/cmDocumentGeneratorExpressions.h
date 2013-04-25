/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2010 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmDocumentGeneratorExpressions_h
#define cmDocumentGeneratorExpressions_h

#define CM_DOCUMENT_ADD_TEST_GENERATOR_EXPRESSIONS                      \
  "Generator expressions are evaluted during build system generation "  \
  "to produce information specific to each build configuration.  "      \
  "Valid expressions are:\n"                                            \
  "  $<0:...>                  = empty string (ignores \"...\")\n"      \
  "  $<1:...>                  = content of \"...\"\n"                  \
  "  $<CONFIG:cfg>             = '1' if config is \"cfg\", else '0'\n"  \
  "  $<CONFIGURATION>          = configuration name\n"                  \
  "  $<BOOL:...>               = '1' if the '...' is true, else '0'\n"  \
  "  $<STREQUAL:a,b>           = '1' if a is STREQUAL b, else '0'\n"    \
  "  $<ANGLE-R>                = A literal '>'. Used to compare "       \
  "strings which contain a '>' for example.\n"                          \
  "  $<COMMA>                  = A literal ','. Used to compare "       \
  "strings which contain a ',' for example.\n"                          \
  "  $<TARGET_FILE:tgt>        = main file (.exe, .so.1.2, .a)\n"       \
  "  $<TARGET_LINKER_FILE:tgt> = file used to link (.a, .lib, .so)\n"   \
  "  $<TARGET_SONAME_FILE:tgt> = file with soname (.so.3)\n"            \
  "where \"tgt\" is the name of a target.  "                            \
  "Target file expressions produce a full path, but _DIR and _NAME "    \
  "versions can produce the directory and file name components:\n"      \
  "  $<TARGET_FILE_DIR:tgt>/$<TARGET_FILE_NAME:tgt>\n"                  \
  "  $<TARGET_LINKER_FILE_DIR:tgt>/$<TARGET_LINKER_FILE_NAME:tgt>\n"    \
  "  $<TARGET_SONAME_FILE_DIR:tgt>/$<TARGET_SONAME_FILE_NAME:tgt>\n"    \
  "\n"                                                                  \
  "  $<TARGET_PROPERTY:tgt,prop>   = The value of the property prop\n"  \
  "on the target tgt. Note that tgt is not added as a dependency of\n"  \
  "the target this expression is evaluated on.\n"                       \
  "Boolean expressions:\n"                                              \
  "  $<AND:?[,?]...>           = '1' if all '?' are '1', else '0'\n"    \
  "  $<OR:?[,?]...>            = '0' if all '?' are '0', else '1'\n"    \
  "  $<NOT:?>                  = '0' if '?' is '1', else '1'\n"         \
  "where '?' is always either '0' or '1'.\n"                            \
  ""

#define CM_DOCUMENT_COMMAND_GENERATOR_EXPRESSIONS                       \
  CM_DOCUMENT_ADD_TEST_GENERATOR_EXPRESSIONS \
  "Expressions with an implicit 'this' target:\n"                       \
  "  $<TARGET_PROPERTY:prop>   = The value of the property prop on\n"   \
  "the target on which the generator expression is evaluated.\n"        \
  ""

#endif
