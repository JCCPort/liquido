#include "OFOS_DetectorMessenger.h"
#include "OFOS_LsMatProperties.h"
#include "OFOS_DetectorConstruction.h"
#include "OFOS_ReadoutUnitGeometry.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"

//#include "CLHEP/Units/SystemOfUnits.h"
#include "G4UnitsTable.hh"


OFOS_DetectorMessenger::OFOS_DetectorMessenger(OFOS_DetectorConstruction *det) : G4UImessenger(),
                                                                                 det_(det) {
    ofos_directory_ = new G4UIdirectory("/OFOS/");
    ofos_directory_->SetGuidance("UI commands to modify OFOS settings");

    ls_directory_ = new G4UIdirectory("/OFOS/ls/");
    ls_directory_->SetGuidance("Liquid Scintillator Parameters");

    geom_directory_ = new G4UIdirectory("/OFOS/geom/");
    geom_directory_->SetGuidance("Geometry Parameters");

    detector_directory_ = new G4UIdirectory("/OFOS/detector/");
    detector_directory_->SetGuidance("Detector-related global commands");

    absorption_length_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/ls/absorption", this);
    absorption_length_cmd_->SetGuidance("LS Absorption Length");
    absorption_length_cmd_->SetParameterName("ls_absorption", false);
    absorption_length_cmd_->SetUnitCategory("Length");
    absorption_length_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    scattering_length_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/ls/scattering", this);
    scattering_length_cmd_->SetGuidance("LS Scattering Length");
    scattering_length_cmd_->SetParameterName("ls_scattering", false);
    scattering_length_cmd_->SetUnitCategory("Length");
    scattering_length_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    // G4UnitDefinition ( "g/cm3" , "g/cm3", "Density", g/cm3 );

    light_yield_cmd_ = new G4UIcmdWithADouble("/OFOS/ls/lightyield", this);
    light_yield_cmd_->SetGuidance("LS Light Yield per MeV");
    light_yield_cmd_->SetParameterName("light_yield", false);
    light_yield_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    birks_cmd_ = new G4UIcmdWithADouble("/OFOS/ls/birks", this);
    birks_cmd_->SetGuidance("LS Birks' Constant [mm/MeV]");
    birks_cmd_->SetParameterName("birks_const", false);
    birks_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    density_cmd_ = new G4UIcmdWithADouble("/OFOS/ls/density", this);
    density_cmd_->SetGuidance("LS Density");
    density_cmd_->SetParameterName("ls_density", false);
//  density_cmd_->SetOmittable(false);
    density_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    loading_fraction_cmd_ = new G4UIcmdWithADouble("/OFOS/ls/loading_fraction", this);
    loading_fraction_cmd_->SetGuidance("Grams of Loading Isotope per Grams of LAB");
    loading_fraction_cmd_->SetParameterName("ls_loading_fraction", false);
    loading_fraction_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    loading_material_cmd_ = new G4UIcmdWithAString("/OFOS/ls/loading_material", this);
    loading_material_cmd_->SetGuidance("Isotope to be loaded in LAB");
    loading_material_cmd_->SetParameterName("ls_loading_material", false);
    loading_material_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);


    /// this command is now embedded in detector/build
    /// in order to deploy ls properties before modifying the geometry
    // deploy_properties_cmd_ =  new G4UIcmdWithoutParameter("/OFOS/ls/deploy_properties", this);
    // deploy_properties_cmd_->SetGuidance("Instantiate LS Material Property Table");
    // deploy_properties_cmd_->AvailableForStates(G4State_PreInit,G4State_Idle);

    num_ru_x_cmd_ = new G4UIcmdWithAnInteger("/OFOS/geom/num_ru_x", this);
    num_ru_x_cmd_->SetGuidance("Number of Readout Units along x");
    num_ru_x_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    num_ru_y_cmd_ = new G4UIcmdWithAnInteger("/OFOS/geom/num_ru_y", this);
    num_ru_y_cmd_->SetGuidance("Number of Readout Units along y");
    num_ru_y_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    num_ru_z_cmd_ = new G4UIcmdWithAnInteger("/OFOS/geom/num_ru_z", this);
    num_ru_z_cmd_->SetGuidance("Number of Readout Units along z");
    num_ru_z_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    vert_ru_geom_cmd_ = new G4UIcmdWithAString("/OFOS/geom/ru_xy_geom", this);
    vert_ru_geom_cmd_->SetGuidance("Geometry of the readout units along the xy plane");
    vert_ru_geom_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    hori_ru_geom_cmd_ = new G4UIcmdWithAString("/OFOS/geom/ru_z_geom", this);
    hori_ru_geom_cmd_->SetGuidance("Geometry of the readout units along the z direction");
    hori_ru_geom_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    vert_ru_distance_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/geom/ru_xy_pitch", this);
    vert_ru_distance_cmd_->SetGuidance("Distance among readout units on the xy plane");
    vert_ru_distance_cmd_->SetUnitCategory("Length");
    vert_ru_distance_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    hori_ru_distance_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/geom/ru_z_pitch", this);
    hori_ru_distance_cmd_->SetGuidance("Distance among readout units along z direction");
    hori_ru_distance_cmd_->SetUnitCategory("Length");
    hori_ru_distance_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    vert_ru_size_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/geom/ru_xy_size", this);
    vert_ru_size_cmd_->SetGuidance("Distance among fibers within a readout unit on the xy plane");
    vert_ru_size_cmd_->SetUnitCategory("Length");
    vert_ru_size_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    hori_ru_size_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/geom/ru_z_size", this);
    hori_ru_size_cmd_->SetGuidance("Distance among finbers within a readout unit along z direction");
    hori_ru_size_cmd_->SetUnitCategory("Length");
    hori_ru_size_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    fiber_rad_cmd_ = new G4UIcmdWithADoubleAndUnit("/OFOS/geom/fiber_radius", this);
    fiber_rad_cmd_->SetGuidance("Fiber Radius");
    fiber_rad_cmd_->SetUnitCategory("Length");
    fiber_rad_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    outer_cladding_cmd_ = new G4UIcmdWithADouble("/OFOS/geom/out_cladding_frac", this);
    outer_cladding_cmd_->SetGuidance("Outer Cladding Fractional Radius");
    outer_cladding_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    inner_cladding_cmd_ = new G4UIcmdWithADouble("/OFOS/geom/inn_cladding_frac", this);
    inner_cladding_cmd_->SetGuidance("Inner Cladding Fractional Radius");
    inner_cladding_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);

    build_geometry_cmd_ = new G4UIcmdWithoutParameter("/OFOS/detector/build", this);
    build_geometry_cmd_->SetGuidance("Build detector");
    build_geometry_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
}



/***********************************************************************************/
/***********************************************************************************/



OFOS_DetectorMessenger::~OFOS_DetectorMessenger() {
    G4cout << ":~OFOS_DetectorMessenger()" << G4endl;
//  delete ofos_directory_;
//  delete ls_directory_;

//  delete absorption_length_cmd_;
//  delete scattering_length_cmd_;
//  delete deploy_properties_cmd_;

//  delete loading_fraction_cmd_;
//  delete loading_material_cmd_;
//  delete deploy_properties_cmd_;

//  delete num_ru_x_cmd_      ;
//  delete num_ru_y_cmd_      ;
//  delete num_ru_z_cmd_      ;
//  delete vert_ru_geom_cmd_    ;
//  delete hori_ru_geom_cmd_     ;
//  delete vert_ru_distance_cmd_   ;
//  delete hori_ru_distance_cmd_    ;
//  delete vert_ru_size_cmd_    ;
//  delete hori_ru_size_cmd_     ;
//  delete fiber_rad_cmd_     ;
//  delete outer_cladding_cmd_;
//  delete inner_cladding_cmd_;
//  delete build_geometry_cmd_;

//  delete  density_cmd_;
//  delete  loading_fraction_cmd_;
//  delete  loading_material_cmd_;

    G4cout << "Done" << G4endl;
}


/***********************************************************************************/
/***********************************************************************************/


void OFOS_DetectorMessenger::SetNewValue(G4UIcommand *command, G4String newValue) {
    if (command == absorption_length_cmd_) {
        det_->set_ls_dummy_absorption(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));
    }

    if (command == scattering_length_cmd_) {
        det_->set_ls_dummy_scattering(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));
    }

    if (command == light_yield_cmd_) { det_->set_ls_light_yield(G4UIcmdWithADouble::GetNewDoubleValue(newValue)); }

    if (command == birks_cmd_) { det_->set_ls_birks(G4UIcmdWithADouble::GetNewDoubleValue(newValue)); }

    if (command == density_cmd_) { det_->set_ls_density(G4UIcmdWithADouble::GetNewDoubleValue(newValue)); }

    if (command == loading_fraction_cmd_) {
        det_->set_ls_loading_fraction(G4UIcmdWithADouble::GetNewDoubleValue(newValue));
    }

    if (command == loading_material_cmd_) { det_->set_ls_loading_material(newValue); }

    /**************/

    // if( command == deploy_properties_cmd_ )
    //     { det_->deploy_ls_properties(); }

    if (command == num_ru_x_cmd_)
        det_->set_number_ru_x(G4UIcmdWithAnInteger::GetNewIntValue(newValue));

    if (command == num_ru_y_cmd_)
        det_->set_number_ru_y(G4UIcmdWithAnInteger::GetNewIntValue(newValue));

    if (command == num_ru_z_cmd_)
        det_->set_number_ru_z(G4UIcmdWithAnInteger::GetNewIntValue(newValue));

    if (command == vert_ru_geom_cmd_)
        det_->set_vert_ru_geometry(newValue);

    if (command == hori_ru_geom_cmd_)
        det_->set_hori_ru_geometry(newValue);

    if (command == vert_ru_distance_cmd_)
        det_->set_vert_ru_dist(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));

    if (command == hori_ru_distance_cmd_)
        det_->set_hori_ru_dist(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));

    if (command == vert_ru_size_cmd_)
        det_->set_vert_ru_size(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));

    if (command == hori_ru_size_cmd_)
        det_->set_hori_ru_size(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));

    if (command == fiber_rad_cmd_)
        det_->set_fiber_radius(G4UIcmdWithADoubleAndUnit::GetNewDoubleValue(newValue));

    if (command == outer_cladding_cmd_)
        det_->set_outer_cladding_fractional_radius(G4UIcmdWithADouble::GetNewDoubleValue(newValue));

    if (command == inner_cladding_cmd_)
        det_->set_inner_cladding_fractional_radius(G4UIcmdWithADouble::GetNewDoubleValue(newValue));

    if (command == build_geometry_cmd_) {
        G4cout << "OFOS_DetectorMessenger :: calling update_geom()" << G4endl;
        det_->update_geom();
    }


}

