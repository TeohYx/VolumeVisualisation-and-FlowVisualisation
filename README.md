# VolumeVisualisation-and-FlowVisualisation

## Note

There are 3 folder in this page. The VolumeVisualisation folder is a project for the Part 1, the FlowVisualisation folder is a project for the Part 2, hedgehog visualisation and glyph-based visualisation, while the Streamline folder is a project for the Part 2, strealine-based visualisation.

The build folder is not included due to the large file of more than 100MB in it. Therefore, to run the code, the configure, generate and run project process have to be done using CMake manually.



## **Part 1 - Volume Visualisation**

### 1A 

#### VTK Volume

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/1f40aada-4033-4037-9947-02078c54451c)

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/cad07af6-2dd5-4cd2-9042-7fe8209a10fa)

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/876a9a67-c95f-4df5-a9ca-0c7b57623242)

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/df0adbbb-9b0b-475a-b7c7-e9b7037c910b)



### 1B

**Question:** How many important surfaces does each of your volumes have? What do these surfaces correspond to (e.g., “skin”)?

    For head: 3 surfaces: Skin, Skull and Teeth. The position surfaces of skin, skull and teeth are 500, 1150 and 2650 respectively.

    For teapot: 2 surfaces: Foremost Surface and Inner Surface. The position surfaces of formost surface and inner surface are 1000 and 4000 respectively.


**Question:** For each volume, setup a transfer function for the dataset that uses appropriate colors and clearly displays multiple relevant iso-surfaces (e.g., the skin and bone from the head dataset shown in class)


  #### Opacity
  
	// For head dataset
	/*
	isoOpacityTransferFunction->AddPoint(0, 0.0);
	isoOpacityTransferFunction->AddPoint(50, 0.1);
	isoOpacityTransferFunction->AddPoint(500, 0.3);		// Skin
	isoOpacityTransferFunction->AddPoint(1150, 0.5);		// Skull
	isoOpacityTransferFunction->AddPoint(1500, 0.7);
	isoOpacityTransferFunction->AddPoint(2650, 1.0);		// Teeth
	*/

	// For teapot dataset
	/*
	isoOpacityTransferFunction->AddPoint(0, 0.0);
	isoOpacityTransferFunction->AddPoint(1000, 0.5);
	isoOpacityTransferFunction->AddPoint(4000, 0.7);
	isoOpacityTransferFunction->AddPoint(8000, 0.9);
	*/


 #### Colors
  
	// For head dataset
	/*
	isoColorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
	isoColorTransferFunction->AddRGBPoint(500.0, 1.0, 0.6, 0.0);		// Skin 1st layer
	isoColorTransferFunction->AddRGBPoint(700.0, 1.0, 0.6, 0.0);		// Skin 2nd layer
	isoColorTransferFunction->AddRGBPoint(800.0, 1.0, 0.0, 0.0);		// Skin 3rd layer
	isoColorTransferFunction->AddRGBPoint(1150.0, 0.8, 0.8, 0.8);	// Skull
	isoColorTransferFunction->AddRGBPoint(2650.0, 1.0, 1.0, 1.0);	// Teeth
	*/

	// For teapot dataset
	/*
	isoColorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
	isoColorTransferFunction->AddRGBPoint(1000.0, 0.5, 1.0, 0.0);		// Foremost Surface
	isoColorTransferFunction->AddRGBPoint(4000.0, 0.3, 0.24, 0.55);		// Inner Surface
	isoColorTransferFunction->AddRGBPoint(8000.0, 0.94, 0.5, 0.5);		// Lobster
	*/


#### **User Controls:**

    s - Toggle between Iso-surface and Ray-marching 

    i - Decrease iso-value
  
    I - Increase iso-value






## **Part 2 - Flow Visualisation**

### 1. Hedgehog Visualisation

Data: testData1.vtk

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/42e2b1b1-be86-4f9c-a4c4-4014d6aebdb9)

Data: testData2.vtk

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/1f61af02-83c4-4709-b6f5-192275781cc5)

Data: carotid.vtk

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/9f7b70fe-88c9-4fa4-8af7-cc5ca7e04335)

### 2. Glyph-based Visualisation

Cone height = 1; Cone radius = 0.3; Scale = 2

Data: testData1.vtk

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/e33678cb-b12c-4eb7-94fb-b22b3427cba4)

Data: testData2.vtk

Scale = 5

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/5fbd80a2-b7c7-4fa3-bcea-0ddf912a00c3)

Data: carotid.vtk

Scale = 0.5

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/1ab32f97-208c-469b-8e67-26fcdf816c10)


### 3. Streamline-based Visualisation

Data: testData1.vtk


![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/be3c5c2e-22c6-4145-8449-0f371a8b72e1)


#### - Sampling Points along Streamlines

![image](https://github.com/TeohYx/VolumeVisualisation-and-FlowVisualisation/assets/67152792/638777a8-3a1a-4e00-a2b2-b0c46710de42)
