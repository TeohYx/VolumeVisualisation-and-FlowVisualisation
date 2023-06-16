#include "vtkRenderer.h"
#include "vtkPointSet.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume16Reader.h"
#include "vtkPolyDataMapper.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkStructuredPointsReader.h"
#include "vtkMarchingCubes.h"
#include "vtkRecursiveDividingCubes.h"
#include "vtkScalarBarWidget.h"
#include "vtkScalarBarActor.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
//#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkFixedPointVolumeRayCastMapper.h"
//#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkStructuredPointsReader.h"
#include "vtkThresholdPoints.h"
#include "vtkMaskPoints.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkVertexGlyphFilter.h"
#include "vtkLookupTable.h"
#include "vtkCommand.h"
#include "vtkHedgeHog.h"
#include "vtkStreamTracer.h"
#include "vtkPoints.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include <vtkPointSource.h>
#include <vtkTubeFilter.h>
#include "vtkPoints.h"
#include <vtkPointData.h>

int main(int argc, char** argv)
{
	
	// Create the renderer, the render window, and the interactor. The renderer
	// draws into the render window, the interactor enables mouse- and 
	// keyboard-based interaction with the data within the render window.
	vtkRenderer* aRenderer = vtkRenderer::New();
	vtkRenderWindow* renWin = vtkRenderWindow::New();

	renWin->AddRenderer(aRenderer);
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	// carotid
	double origin[3] = { 100.0, 80.0, 1.0 };

	// Read
	vtkStructuredPointsReader* reader = vtkStructuredPointsReader::New();
	reader->SetFileName("../data/testData1.vtk");
	reader->Update();

	vtkTransform* transform = vtkTransform::New();
	transform->Translate(-origin[0], -origin[1], -origin[2]);

	vtkSmartPointer<vtkTransformFilter> transformFilter =
		vtkSmartPointer<vtkTransformFilter>::New();
	transformFilter->SetInputConnection(reader->GetOutputPort());
	transformFilter->SetTransform(transform);
	transformFilter->Update();

	// Lookup Table
	vtkLookupTable* lut = vtkLookupTable::New();
	lut->SetHueRange(0.667, 0.0);
	lut->Build();

	// Glyph-based visualization using cones
	vtkConeSource* coneSource = vtkConeSource::New();
	// Set any properties for the cone source if desired (e.g., height, radius, resolution).

	vtkStreamTracer* streamline1 = vtkStreamTracer::New();

	vtkPointSet* seedPoint = vtkPointSet::New();
	vtkPoints* points = vtkPoints::New();

	// Define the grid parameters

	// testData1
	
	int xSize = 36;  // Number of points in x-direction
	int ySize = 36;  // Number of points in y-direction
	int zSize = 2;  // Number of points in z-direction


	// testData1
	
	int maxX = 36;
	int minX = 0;
	int maxY = 36;
	int minY = 0;
	int maxZ = 0;
	int minZ = 0;
	
			// Compute the spacing between the grid points
	double xSpacing = (maxX - minX) / (xSize - 1);
	double ySpacing = (maxY - minY) / (ySize - 1);
	double zSpacing = (maxZ - minZ) / (zSize - 1);

	// Generate the grid of seed points
	for (int k = 0; k < zSize; k++) {
		for (int j = 0; j < ySize; j++) {
			for (int i = 0; i < xSize; i++) {
				double point[3];
				point[0] = minX + i * xSpacing;
				point[1] = minY + j * ySpacing;
				point[2] = minZ + k * zSpacing;
				points->InsertNextPoint(point);
			}
		}
	}

	seedPoint->SetPoints(points);

	vtkPolyData* polyData = vtkPolyData::New();
	polyData->SetPoints(points);

	// streamline1 reader replaced with transformFilter if carotid is used, using reader if testData1/testData2 is used
	streamline1->SetInputConnection(reader->GetOutputPort());
	streamline1->SetSourceData(polyData);
	streamline1->SetIntegrationDirectionToBoth();
	streamline1->SetMaximumPropagation(200);	// Can change value
	streamline1->SetIntegrationStepUnit(0.2);	// Can change value
	streamline1->Update();

	vtkPolyDataMapper* streamline = vtkPolyDataMapper::New();
	streamline->SetInputConnection(streamline1->GetOutputPort());
	streamline->SetScalarRange(0.0, 1.0);
	streamline->SetLookupTable(lut);

	vtkActor* streamLineActor = vtkActor::New();
	streamLineActor->SetMapper(streamline);

	aRenderer->AddActor(streamLineActor);

	// Set a background color for the renderer and set the size of the
	// render window (expressed in pixels).
	aRenderer->SetBackground(0, 0, 0);
	renWin->SetSize(800, 600);

	// Initialize the event loop and then start it.
	iren->Initialize();
	renWin->SetWindowName("Simple Volume Renderer");
	renWin->Render();
	iren->Start();

	return 0;

	
	
	/*
	
	//Last Question

	// Create the renderer, the render window, and the interactor. The renderer
	// draws into the render window, the interactor enables mouse- and
	// keyboard-based interaction with the data within the render window.
	vtkRenderer* aRenderer = vtkRenderer::New();
	vtkRenderWindow* renWin = vtkRenderWindow::New();
	renWin->AddRenderer(aRenderer);
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	// Read
	vtkStructuredPointsReader* reader = vtkStructuredPointsReader::New();
	vtkStructuredPointsReader* reader3 = vtkStructuredPointsReader::New();
	reader->SetFileName("../data/testData1.vtk");
	reader3->SetFileName("../data/carotid.vtk");
	reader->Update();
	reader3->Update();


	// Hedgehog setup.
	 vtkHedgeHog* hhog = vtkHedgeHog::New();
	 hhog->SetInputConnection(reader->GetOutputPort());
	 hhog->SetScaleFactor(2);


	 //glyph
	vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
	cone->SetResolution(11);
	cone->SetHeight(1);
	cone->SetRadius(0.25);
	vtkGlyph3D* glyph = vtkGlyph3D::New();
	glyph->SetInputConnection(reader3->GetOutputPort());
	glyph->SetSourceConnection(cone->GetOutputPort());
	glyph->SetScaleFactor(0.5);
	glyph->SetScaleModeToScaleByVector();
	glyph->Update();
	vtkNew<vtkPointSource> psource;
	psource->SetNumberOfPoints(25);
	psource->SetCenter(133.1, 116.3, 5.0);
	//psource->SetCenter(100, 40, 40);
	psource->SetRadius(2.0);
	vtkNew<vtkThresholdPoints> threshold;
	threshold->SetInputConnection(reader->GetOutputPort());
	threshold->ThresholdByUpper(275);
	vtkNew<vtkStreamTracer> streamers;
	streamers->SetInputConnection(reader3->GetOutputPort());
	streamers->SetSourceConnection(psource->GetOutputPort());
	// streamers->SetMaximumPropagationUnitToTimeUnit();
	streamers->SetMaximumPropagation(100.0);
	// streamers->SetInitialIntegrationStepUnitToCellLengthUnit();
	streamers->SetInitialIntegrationStep(0.2);
	streamers->SetTerminalSpeed(.01);
	streamers->Update();
	double range[2];
	range[0] =
		streamers->GetOutput()->GetPointData()->GetScalars()->GetRange()[0];
	range[1] =
		streamers->GetOutput()->GetPointData()->GetScalars()->GetRange()[1];
	vtkNew<vtkTubeFilter> tubes;
	tubes->SetInputConnection(streamers->GetOutputPort());
	tubes->SetRadius(0.3);
	tubes->SetNumberOfSides(6);
	tubes->SetVaryRadius(0);


	// Lookup Table
	vtkLookupTable* lut = vtkLookupTable::New();
	lut->SetHueRange(0.667, 0.0);
	lut->Build();


	// Poly Mapper
	vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
	//mapper->SetInputConnection(hhog->GetOutputPort());
	mapper->SetInputConnection(tubes->GetOutputPort());
	mapper->SetScalarRange(range[0], range[1]);
	mapper->SetLookupTable(lut);


	// Poly Mapper2
	vtkPolyDataMapper* mapper1 = vtkPolyDataMapper::New();
	//mapper->SetInputConnection(hhog->GetOutputPort());
	mapper1->SetInputConnection(glyph->GetOutputPort());
	mapper1->SetScalarRange(0.0, 1.0);
	mapper1->SetLookupTable(lut);


	// Actor
	vtkActor* actor = vtkActor::New();
	actor->SetMapper(mapper);
	vtkActor* actor1 = vtkActor::New();
	actor1->SetMapper(mapper1);
	// Actors are added to the renderer. An initial camera view is created.
// The Dolly() method moves the camera towards the FocalPoint,
// thereby enlarging the image.
	aRenderer->AddActor(actor);
	aRenderer->AddActor(actor1);
	// Set a background color for the renderer and set the size of the
	// render window (expressed in pixels).
	aRenderer->SetBackground(0, 0, 0);
	renWin->SetSize(800, 600);
	// Initialize the event loop and then start it.
	iren->Initialize();
	renWin->SetWindowName("Simple Volume Renderer");
	renWin->Render();
	iren->Start();
	return 0;
	*/
}

