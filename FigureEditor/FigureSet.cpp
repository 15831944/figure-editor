#include "stdafx.h"
#include "FigureSet.h"

Observable::Observable(){}

Observable::~Observable(){}

void Observable::attach(IObserver* observer){
	auto it = find(observers.begin(), observers.end(), observer);
	if (it == observers.end())
		observers.push_back(observer);
}

void Observable::detach(IObserver* observer){
	auto it = find(observers.begin(), observers.end(), observer);
	if (it != observers.end())
		observers.erase(it);
}

void Observable::notifyObservers(){
	for (auto it = observers.begin(); it != observers.end(); ++it)
		(*it)->update();
}

FigureSet::FigureSet() : m_pDBEditor(NULL){}

FigureSet::~FigureSet(){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); it = m_Figures.erase(it))
		delete (*it);
	delete m_pDBEditor;
}


void FigureSet::addFigure(Figure* pFigure){
	m_Figures.push_back(pFigure);
}


void FigureSet::updateFigure(int index, Figure* pNewFigure){
	if (index < m_Figures.size()) {
		delete m_Figures[index];
		m_Figures[index] = pNewFigure;
	}
}


void FigureSet::selectFigure(int index){
	if (index < m_Figures.size())
		m_Figures[index]->pick();
}


void FigureSet::unselectFigures(){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
		(*it)->unpick();
}


void FigureSet::moveSelectedFigures(double moveX, double moveY, double moveZ){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
		if ((*it)->picked)
			(*it)->move(moveX, moveY, moveZ);
}


void FigureSet::scaleSelectedFigures(double zoom){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked)
		(*it)->scale(zoom);
}


void FigureSet::rotateSelectedFiguresAroundOwnAxis(double angle, bool x, bool y, bool z){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked){
		if (x)
			(*it)->rotateX += angle;
		if (y)
			(*it)->rotateY += angle;
		if (z)
			(*it)->rotateZ += angle;
	}
}


void FigureSet::rotateSelectedFiguresAroundCoordAxis(double angle, bool ox, bool oy, bool oz){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked)
		(*it)->rotate(angle, ox, oy, oz);
}


void FigureSet::changeSelectedFiguresColor(double red, double green, double blue){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked)
		(*it)->changeColor(red, green, blue);
}


void FigureSet::projectSelectedFigures(bool xoy, bool yoz, bool xoz){
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked) {
		(*it)->projectedXOY = xoy;
		(*it)->projectedYOZ = yoz;
		(*it)->projectedXOZ = xoz;
	}
}


void FigureSet::deleteSelectedFigures(){
	auto it = m_Figures.begin();
	while (it != m_Figures.end())
	{
		if ((*it)->picked) {
			delete *it;
			it = m_Figures.erase(it);
		}
		else ++it;
	}
}


int FigureSet::getSelectedFiguresNumber() const {
	int result(0);
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	if ((*it)->picked)
		++result;
	return result;
}



Figure* FigureSet::getSelectedFigure(int& index) const {
	for (int i = 0; i < m_Figures.size(); i++)
	{
		if (m_Figures[i]->picked)
		{
			index = i;
			return m_Figures[i];
		}
	}
	index = 0;
	return NULL;
}


void FigureSet::markIntersectedFigures()
{
	for (auto it = m_Figures.begin(); it != m_Figures.end(); ++it)
	{
		(*it)->intersected = false;
	}

	for (auto itPickedFigure = m_Figures.begin(); itPickedFigure != m_Figures.end(); ++itPickedFigure)
	{
		if (!((*itPickedFigure)->picked)) continue;

		for (auto itOtherFigure = m_Figures.begin(); itOtherFigure != m_Figures.end(); ++itOtherFigure)
		{
			if (itOtherFigure == itPickedFigure) continue;

			if ((*itPickedFigure)->intersectsFigure(*itOtherFigure))
			{
				(*itPickedFigure)->intersected = true;
				(*itOtherFigure)->intersected = true;
			}
		}
	}
}


void FigureSet::setDBEditor(FigureDatabaseEditor* pDBEditor)
{
	m_pDBEditor = pDBEditor;
}

void FigureSet::saveDatabase()
{
	if (m_pDBEditor)
		m_pDBEditor->saveDatabase();
}


void FigureSet::loadDatabase()
{
	if (m_pDBEditor)
		m_pDBEditor->loadDatabase();
}
