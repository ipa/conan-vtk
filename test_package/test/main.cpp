#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkCallbackCommand.h>
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkVRMLImporter.h"
#include "vtkAutoInit.h"
#include <vtkVersion.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);

vtkSmartPointer<vtkRenderWindow> renderWindow;
vtkSmartPointer<vtkRenderer> renderer;

void KeypressCallbackFunction (
        vtkObject* caller,
        long unsigned int vtkNotUsed(eventId),
        void* vtkNotUsed(clientData),
        void* vtkNotUsed(callData) )
{

    auto *iren = static_cast<vtkRenderWindowInteractor*>(caller);

    std::string keyPressed = iren->GetKeySym();
    std::cout << keyPressed << std::endl;
    if(keyPressed == "Escape"){
        iren->GetRenderWindow()->Finalize();
        iren->TerminateApp();
    } else if (keyPressed == "f") {
        bool isFullScreen = static_cast<bool>(renderWindow->GetFullScreen());
        renderWindow->SetFullScreen(!isFullScreen);
        renderWindow->Render();
        iren->Start();
        //std::cout << "foo" + renderWindow->GetFullScreen() << std::endl;
        //renderWindow->Render();
    } else if (keyPressed == "space"){
        vtkSmartPointer<vtkCamera>tmpCam = renderer->GetActiveCamera();
        std::cout << tmpCam->GetViewUp()[0] << ", " << tmpCam->GetViewUp()[1] << ", " <<tmpCam->GetViewUp()[2] << ", " << std::endl;
        std::cout << tmpCam->GetFocalPoint()[0] << ", " << tmpCam->GetFocalPoint()[1] << ", " <<tmpCam->GetFocalPoint()[2] << ", " << std::endl;
        std::cout << tmpCam->GetDistance() << std::endl;
    }
}

int main(int, char *[]) {
    std::cout << vtkVersion::GetVTKSourceVersion() << std::endl;
    std::cout << vtkVersion::GetVTKMajorVersion() << std::endl;
    std::cout << vtkVersion::GetVTKMinorVersion() << std::endl;

    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e, in practice an octagonal prism).
    vtkSmartPointer<vtkCylinderSource> cylinder =
            vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(8);
    cylinder->SetRadius(10);
    cylinder->SetHeight(20);

    // The mapper is responsible for pushing the geometry into the graphics library.
    // It may also do color mapping, if scalars or other attributes are defined.
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());



    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkSmartPointer<vtkActor> cylinderActor =
            vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);


    // The renderer generates the image
    // which is then displayed on the render window.
    // It can be thought of as a scene to which the actor is added
    renderer = vtkSmartPointer<vtkRenderer>::New();

    //renderer->AddActor(cylinderActor);
    //renderer->SetBackground(0.1, 0.2, 0.4);
    // Zoom in a little by accessing the camera and invoking its "Zoom" method.
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(0.75);

    // The render window is the actual GUI window
    // that appears on the computer screen
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(1920, 1080);
    renderWindow->AddRenderer(renderer);
    renderWindow->StereoCapableWindowOn();
    //renderWindow->SetStereoTypeToCrystalEyes();
    renderWindow->SetStereoTypeToInterlaced();
    //renderWindow->SetStereoTypeToSplitViewportHorizontal();
    //renderWindow->SetStereoTypeToAnaglyph ();
    renderWindow->StereoRenderOn();


    // The render window interactor captures mouse events
    // and will perform appropriate camera or actor manipulation
    // depending on the nature of the events.
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkCallbackCommand> keypressCallback =
            vtkSmartPointer<vtkCallbackCommand>::New();
    keypressCallback->SetCallback ( KeypressCallbackFunction );
    renderWindowInteractor->AddObserver (
            vtkCommand::KeyPressEvent,
            keypressCallback );

    renderWindowInteractor->SetRenderWindow(renderWindow);
    vtkInteractorStyleTrackballCamera *style =
         vtkInteractorStyleTrackballCamera::New();
    renderWindowInteractor->SetInteractorStyle(style);


    // VRML Import
    vtkSmartPointer<vtkVRMLImporter> importer = vtkSmartPointer<vtkVRMLImporter>::New();
    importer->SetFileName ( "data/liver.wrl" );
    importer->SetRenderWindow(renderWindow);
    importer->Update();

    vtkSmartPointer<vtkCamera>tmpCam = renderer->GetActiveCamera();
    tmpCam->SetFocalPoint(-60.9041, 106.832, -316.343);
    tmpCam->SetViewUp(-0.659495, -0.401554, 0.635469);

    //tmpCam->SetDistance(184.415);
    // This starts the event loop and as a side effect causes an initial render.
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
}
/*


*/
