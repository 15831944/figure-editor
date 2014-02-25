///////////////////////////////////////////////////////////
//  IController.cpp
//  Implementation of the Class IController
//  Created on:      20-Êâ³-2014 20:02:56
//  Original author: Àðòåì
///////////////////////////////////////////////////////////

#include "IController.h"


IController::IController(){

}



IController::~IController(){

}





IController::DoubleClickOnFigure(UINT nFlags, int index){

}


IController::LButtonDown(UINT nFlags, CPoint point){

}


IController::RButtonDown(UINT nFlags, CPoint point){

}


IController::MouseMove(UINT nFlags, CPoint point){

}


IController::MouseWheel(UINT nFlags, short zDelta, CPoint pt){

}


IController::AddCuboid(Cuboid* cuboid){

}


IController::AddEllipsoid(Ellipsoid* ellipsoid){

}


IController::UpdateFigure(int index, Figure* pNewFigure){

}


IController::Rotate(double angle, bool ox, bool oy, bool oz){

}


IController::ChangeColor(double red, double green, double blue){

}


IController::Project(bool xoy, bool yoz, bool xoz){

}


IController::Delete(){

}


IController::SaveDatabase(){

}


IController::LoadDatabase(){

}