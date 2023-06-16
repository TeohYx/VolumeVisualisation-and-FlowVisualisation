/*=========================================================================
    Program:   Visualization Toolkit
    Module:    vtkStreamer.h

    Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
    All rights reserved.
    See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

    This software is distributed WITHOUT ANY WARRANTY; without even
    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the above copyright notice for more information.
=========================================================================*/

#ifndef vtkStreamer_h
#define vtkStreamer_h

#include "vtkFiltersFlowPathsModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class vtkInitialValueProblemSolver;
class vtkMultiThreader;

#ifndef VTK_LEGACY_REMOVE

#define VTK_INTEGRATE_FORWARD 0
#define VTK_INTEGRATE_BACKWARD 1
#define VTK_INTEGRATE_BOTH_DIRECTIONS 2

class VTKFILTERSFLOWPATHS_EXPORT vtkStreamer : public vtkPolyDataAlgorithm
{
public:
    vtkTypeMacro(vtkStreamer, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent);

    void SetStartLocation(vtkIdType cellId, int subId, double pcoords[3]);

    void SetStartLocation(vtkIdType cellId, int subId, double r, double s,
        double t);

    vtkIdType GetStartLocation(int& subId, double pcoords[3]);

    void SetStartPosition(double x[3]);

    void SetStartPosition(double x, double y, double z);

    double* GetStartPosition();

    void SetSourceData(vtkDataSet* source);
    vtkDataSet* GetSource();

    void SetSourceConnection(vtkAlgorithmOutput* algOutput);

    vtkSetClampMacro(MaximumPropagationTime, double, 0.0, VTK_DOUBLE_MAX);
    vtkGetMacro(MaximumPropagationTime, double);

    vtkSetClampMacro(IntegrationDirection, int,
        VTK_INTEGRATE_FORWARD, VTK_INTEGRATE_BOTH_DIRECTIONS);
    vtkGetMacro(IntegrationDirection, int);
    void SetIntegrationDirectionToForward()
    {
        this->SetIntegrationDirection(VTK_INTEGRATE_FORWARD);
    };
    void SetIntegrationDirectionToBackward()
    {
        this->SetIntegrationDirection(VTK_INTEGRATE_BACKWARD);
    };
    void SetIntegrationDirectionToIntegrateBothDirections()
    {
        this->SetIntegrationDirection(VTK_INTEGRATE_BOTH_DIRECTIONS);
    };
    const char* GetIntegrationDirectionAsString();

    vtkSetClampMacro(IntegrationStepLength, double, 0.0000001, VTK_DOUBLE_MAX);
    vtkGetMacro(IntegrationStepLength, double);

    vtkSetMacro(SpeedScalars, int);
    vtkGetMacro(SpeedScalars, int);
    vtkBooleanMacro(SpeedScalars, int);

    vtkSetMacro(OrientationScalars, int);
    vtkGetMacro(OrientationScalars, int);
    vtkBooleanMacro(OrientationScalars, int);

    vtkSetClampMacro(TerminalSpeed, double, 0.0, VTK_DOUBLE_MAX);
    vtkGetMacro(TerminalSpeed, double);

    vtkSetMacro(Vorticity, int);
    vtkGetMacro(Vorticity, int);
    vtkBooleanMacro(Vorticity, int);

    vtkSetMacro(NumberOfThreads, int);
    vtkGetMacro(NumberOfThreads, int);

    vtkSetMacro(SavePointInterval, double);
    vtkGetMacro(SavePointInterval, double);

    void SetIntegrator(vtkInitialValueProblemSolver*);
    vtkGetObjectMacro(Integrator, vtkInitialValueProblemSolver);

    vtkSetMacro(Epsilon, double);
    vtkGetMacro(Epsilon, double);

protected:

    vtkStreamer();
    ~vtkStreamer();

    void Integrate(vtkDataSet* input, vtkDataSet* source);

    int StartFrom;
    vtkIdType StartCell;
    int StartSubId;
    double StartPCoords[3];
    double StartPosition[3];

    class StreamPoint {
    public:
        double    x[3];
        vtkIdType cellId;
        int       subId;
        double    p[3];
        double    v[3];
        double    speed;
        double    s;
        double    t;
        double    d;
        double    omega;
        double    theta;
    };

    class StreamArray;
    friend class StreamArray;
    class StreamArray {
    public:
        StreamArray();
        ~StreamArray()
        {
            delete[] this->Array;
        };
        vtkIdType GetNumberOfPoints() { return this->MaxId + 1; };
        StreamPoint* GetStreamPoint(vtkIdType i) { return this->Array + i; };
        vtkIdType InsertNextStreamPoint()
        {
            if (++this->MaxId >= this->Size)
            {
                this->Resize(this->MaxId);
            }
            return this->MaxId;
        }
        StreamPoint* Resize(vtkIdType sz);
        void Reset() { this->MaxId = -1; };

        StreamPoint* Array;
        vtkIdType MaxId;
        vtkIdType Size;
        vtkIdType Extend;
        double Direction;
    };

    StreamArray* Streamers;
    vtkIdType NumberOfStreamers;
    double MaximumPropagationTime;
    int IntegrationDirection;
    double IntegrationStepLength;
    int Vorticity;
    double TerminalSpeed;
    int SpeedScalars;
    int OrientationScalars;
    vtkInitialValueProblemSolver* Integrator;
    double Epsilon;
    double SavePointInterval;

    static VTK_THREAD_RETURN_TYPE ThreadedIntegrate(void* arg);

    vtkGetMacro(NumberOfStreamers, vtkIdType);
    StreamArray* GetStreamers() { return this->Streamers; };

    void InitializeThreadedIntegrate();
    vtkMultiThreader* Threader;
    int NumberOfThreads;

    virtual int FillInputPortInformation(int port, vtkInformation* info);

private:
    vtkStreamer(const vtkStreamer&) VTK_DELETE_FUNCTION;
    void operator=(const vtkStreamer&) VTK_DELETE_FUNCTION;
};

inline const char* vtkStreamer::GetIntegrationDirectionAsString()
{
    if (this->IntegrationDirection == VTK_INTEGRATE_FORWARD)
    {
        return "IntegrateForward";
    }
    else if (this->IntegrationDirection == VTK_INTEGRATE_BACKWARD)
    {
        return "IntegrateBackward";
    }
    else
    {
        return "IntegrateBothDirections";
    }
}

#endif // VTK_LEGACY_REMOVE
#endif