// Set Colours for visualisation

#include "PIMPSetVisColours.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"
#include "G4ios.hh"

  
PIMPSetVisColours::PIMPSetVisColours()
{
  // Some visualization styles
  Green = new G4VisAttributes(G4Colour(0.,1.,0.));  // Green
  Green->SetVisibility(true);
  Green->SetForceSolid(TRUE);
  
  RoyalBlue = new G4VisAttributes(G4Colour(0.,0.,1.));  // Royal Blue
  RoyalBlue->SetVisibility(true);
  RoyalBlue->SetForceSolid(TRUE);
  
  Red = new G4VisAttributes(G4Colour(1.,0.,0.));  // Red
  Red->SetVisibility(true);
  Red->SetForceSolid(TRUE);
  
  Yellow = new G4VisAttributes(G4Colour(1.,1.,0.));  // Yellow
  Yellow->SetVisibility(true);
  Yellow->SetForceSolid(TRUE);

  Purple = new G4VisAttributes(G4Colour(1.,0.,1.));  // Purple
  Purple->SetVisibility(true);
  Purple->SetForceSolid(TRUE);

  Black = new G4VisAttributes(G4Colour(0.,0.,0.));  // Black
  Black->SetVisibility(true);
  Black->SetForceSolid(TRUE);
  
  SkyBlue= new G4VisAttributes(G4Colour(0.,1.,1.));  // Sky Blue
  SkyBlue->SetVisibility(true);
  SkyBlue->SetForceSolid(TRUE);

  White= new G4VisAttributes(G4Colour(1.,1.,1.));  // White
  White->SetVisibility(true);
  White->SetForceSolid(TRUE);

  Grey= new G4VisAttributes(G4Colour(0.5,0.5,0.5));  // White
  Grey->SetVisibility(true);
  Grey->SetForceSolid(TRUE);

  DarkRed= new G4VisAttributes(G4Colour(0.5,0.,0.));  // White
  DarkRed->SetVisibility(true);
  DarkRed->SetForceSolid(TRUE);

  DarkYellow= new G4VisAttributes(G4Colour(0.5,0.5,0.));  // White
  DarkYellow->SetVisibility(true);
  DarkYellow->SetForceSolid(TRUE);

  Orange= new G4VisAttributes(G4Colour(1.,0.5,0.));  // White
  Orange->SetVisibility(true);
  Orange->SetForceSolid(TRUE);
 
  Pink= new G4VisAttributes(G4Colour(1.,0.25,0.5));  // White
  Pink->SetVisibility(true);
  Pink->SetForceSolid(TRUE);



}

PIMPSetVisColours::~PIMPSetVisColours()
{;}


