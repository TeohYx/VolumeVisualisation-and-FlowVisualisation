/*=========================================================================
    2
    3   Program:   Visualization Toolkit
    4   Module:    vtkStreamLine.h
    5
    6   Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
    7   All rights reserved.
    8   See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
    9
   10      This software is distributed WITHOUT ANY WARRANTY; without even
   11      the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   12      PURPOSE.  See the above copyright notice for more information.
   13
   14 =========================================================================*/
#ifndef vtkStreamLine_h
#define vtkStreamLine_h

#include "vtkFiltersFlowPathsModule.h" // For export macro
#include "vtkStreamer.h"

#ifndef VTK_LEGACY_REMOVE

class VTKFILTERSFLOWPATHS_EXPORT vtkStreamLine : public vtkStreamer
{
public:
      vtkTypeMacro(vtkStreamLine, vtkStreamer);
      void PrintSelf(ostream & os, vtkIndent indent);
    
          static vtkStreamLine * New();
   
       
          vtkSetClampMacro(StepLength, double, 0.000001, VTK_DOUBLE_MAX);
      vtkGetMacro(StepLength, double);
  
protected:
      vtkStreamLine();
      ~vtkStreamLine() {}

          // Convert streamer array into vtkPolyData
          virtual int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);
   
          // the length of line primitives
          double StepLength;
    
private:
      vtkStreamLine(const vtkStreamLine&) VTK_DELETE_FUNCTION;
      void operator=(const vtkStreamLine&) VTK_DELETE_FUNCTION;
    };

#endif // VTK_LEGACY_REMOVE
#endif