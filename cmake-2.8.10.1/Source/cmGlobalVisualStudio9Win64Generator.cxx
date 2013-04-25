/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmGlobalVisualStudio9Win64Generator.h"
#include "cmLocalVisualStudio7Generator.h"
#include "cmMakefile.h"


cmGlobalVisualStudio9Win64Generator::cmGlobalVisualStudio9Win64Generator()
{
  this->ArchitectureId = "x64";
}

//----------------------------------------------------------------------------
void cmGlobalVisualStudio9Win64Generator
::GetDocumentation(cmDocumentationEntry& entry) const
{
  entry.Name = this->GetName();
  entry.Brief = "Generates Visual Studio 9 2008 Win64 project files.";
  entry.Full = "";
}

//----------------------------------------------------------------------------
void cmGlobalVisualStudio9Win64Generator
::AddPlatformDefinitions(cmMakefile* mf)
{
  cmGlobalVisualStudio9Generator::AddPlatformDefinitions(mf);
  mf->AddDefinition("CMAKE_FORCE_WIN64", "TRUE");
}
