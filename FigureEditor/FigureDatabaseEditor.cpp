#include "stdafx.h"
#include "FigureDatabaseEditor.h"
#include "Figure.h"
#include "Cuboid.h"
#include "Ellipsoid.h"

FigureDatabaseEditor::FigureDatabaseEditor(FigureSet* model, CCuboidSet* pCuboidSet, CEllipsoidSet* pEllipsoidSet)
{
	m_pModel = model;
	m_pCuboidSet = pCuboidSet;
	m_pEllipsoidSet = pEllipsoidSet;
	if (m_pModel)
		m_pModel->setDBEditor(this);
	
	// openig database
	ASSERT(m_pCuboidSet != nullptr);
	if (!m_pCuboidSet->IsOpen())
		m_pCuboidSet->Open();
	ASSERT(m_pEllipsoidSet != nullptr);
	if (!m_pEllipsoidSet->IsOpen())
		m_pEllipsoidSet->Open();
}

FigureDatabaseEditor::~FigureDatabaseEditor()
{
	if (m_pCuboidSet->IsOpen())
		m_pCuboidSet->Close();
	if (m_pEllipsoidSet->IsOpen())
		m_pEllipsoidSet->Close();
}

void FigureDatabaseEditor::saveDatabase()
{
	saveCuboidDB();
	saveEllipsoidDB();
}

void FigureDatabaseEditor::loadDatabase()
{
	for (int i = 0; i < m_pModel->m_Figures.size(); i++)
		m_pModel->selectFigure(i);
	m_pModel->deleteSelectedFigures();

	loadCuboidDB();
	loadEllipsoidDB();
}

void FigureDatabaseEditor::saveCuboidDB()
{
	if (!m_pCuboidSet->IsBOF())
		m_pCuboidSet->MoveFirst();

	// deleting old records
	while (!m_pCuboidSet->IsEOF())
	{
		m_pCuboidSet->Delete();
		m_pCuboidSet->MoveNext();
	}
	m_pCuboidSet->Requery();

	// writing new records
	for (auto it = m_pModel->m_Figures.begin(); it != m_pModel->m_Figures.end(); ++it)
	if (typeid(*(*it)) == typeid(Cuboid))
	{
		Cuboid* pCuboid = dynamic_cast<Cuboid*>(*it);
		m_pCuboidSet->AddNew();

		m_pCuboidSet->m_LENGTH = pCuboid->length;
		m_pCuboidSet->m_HEIGHT = pCuboid->height;
		m_pCuboidSet->m_WIDTH = pCuboid->width;
		m_pCuboidSet->m_MOVE_X = pCuboid->moveX;
		m_pCuboidSet->m_MOVE_Y = pCuboid->moveY;
		m_pCuboidSet->m_MOVE_Z = pCuboid->moveZ;
		m_pCuboidSet->m_ROTATE_X = pCuboid->rotateX;
		m_pCuboidSet->m_ROTATE_Y = pCuboid->rotateY;
		m_pCuboidSet->m_ROTATE_Z = pCuboid->rotateZ;
		m_pCuboidSet->m_ZOOM = pCuboid->zoom;
		m_pCuboidSet->m_TOP_RED = pCuboid->faceColor[0][0];
		m_pCuboidSet->m_TOP_GREEN = pCuboid->faceColor[0][1];
		m_pCuboidSet->m_TOP_BLUE = pCuboid->faceColor[0][2];
		m_pCuboidSet->m_BOTTOM_RED = pCuboid->faceColor[1][0];
		m_pCuboidSet->m_BOTTOM_GREEN = pCuboid->faceColor[1][1];
		m_pCuboidSet->m_BOTTOM_BLUE = pCuboid->faceColor[1][2];
		m_pCuboidSet->m_FRONT_RED = pCuboid->faceColor[2][0];
		m_pCuboidSet->m_FRONT_GREEN = pCuboid->faceColor[2][1];
		m_pCuboidSet->m_FRONT_BLUE = pCuboid->faceColor[2][2];
		m_pCuboidSet->m_BACK_RED = pCuboid->faceColor[3][0];
		m_pCuboidSet->m_BACK_GREEN = pCuboid->faceColor[3][1];
		m_pCuboidSet->m_BACK_BLUE = pCuboid->faceColor[3][2];
		m_pCuboidSet->m_LEFT_RED = pCuboid->faceColor[4][0];
		m_pCuboidSet->m_LEFT_GREEN = pCuboid->faceColor[4][1];
		m_pCuboidSet->m_LEFT_BLUE = pCuboid->faceColor[4][2];
		m_pCuboidSet->m_RIGHT_RED = pCuboid->faceColor[5][0];
		m_pCuboidSet->m_RIGHT_GREEN = pCuboid->faceColor[5][1];
		m_pCuboidSet->m_RIGHT_BLUE = pCuboid->faceColor[5][2];

		if (m_pCuboidSet->CanUpdate())
			m_pCuboidSet->Update();
		m_pCuboidSet->Requery();
	}
}


void FigureDatabaseEditor::loadCuboidDB()
{
	m_pCuboidSet->Requery();

	if (!m_pCuboidSet->IsBOF())
		m_pCuboidSet->MoveFirst();

	while (!m_pCuboidSet->IsEOF())
	{
		Cuboid* pCuboid = new Cuboid;
		
		pCuboid->length = m_pCuboidSet->m_LENGTH;
		pCuboid->height = m_pCuboidSet->m_HEIGHT;
		pCuboid->width = m_pCuboidSet->m_WIDTH;
		pCuboid->moveX = m_pCuboidSet->m_MOVE_X;
		pCuboid->moveY = m_pCuboidSet->m_MOVE_Y;
		pCuboid->moveZ = m_pCuboidSet->m_MOVE_Z;
		pCuboid->rotateX = m_pCuboidSet->m_ROTATE_X;
		pCuboid->rotateY = m_pCuboidSet->m_ROTATE_Y;
		pCuboid->rotateZ = m_pCuboidSet->m_ROTATE_Z;
		pCuboid->zoom = m_pCuboidSet->m_ZOOM;
		pCuboid->faceColor[0][0] = m_pCuboidSet->m_TOP_RED;
		pCuboid->faceColor[0][1] = m_pCuboidSet->m_TOP_GREEN;
		pCuboid->faceColor[0][2] = m_pCuboidSet->m_TOP_BLUE;
		pCuboid->faceColor[1][0] = m_pCuboidSet->m_BOTTOM_RED;
		pCuboid->faceColor[1][1] = m_pCuboidSet->m_BOTTOM_GREEN;
		pCuboid->faceColor[1][2] = m_pCuboidSet->m_BOTTOM_BLUE;
		pCuboid->faceColor[2][0] = m_pCuboidSet->m_FRONT_RED;
		pCuboid->faceColor[2][1] = m_pCuboidSet->m_FRONT_GREEN;
		pCuboid->faceColor[2][2] = m_pCuboidSet->m_FRONT_BLUE;
		pCuboid->faceColor[3][0] = m_pCuboidSet->m_BACK_RED;
		pCuboid->faceColor[3][1] = m_pCuboidSet->m_BACK_GREEN;
		pCuboid->faceColor[3][2] = m_pCuboidSet->m_BACK_BLUE;
		pCuboid->faceColor[4][0] = m_pCuboidSet->m_LEFT_RED;
		pCuboid->faceColor[4][1] = m_pCuboidSet->m_LEFT_GREEN;
		pCuboid->faceColor[4][2] = m_pCuboidSet->m_LEFT_BLUE;
		pCuboid->faceColor[5][0] = m_pCuboidSet->m_RIGHT_RED;
		pCuboid->faceColor[5][1] = m_pCuboidSet->m_RIGHT_GREEN;
		pCuboid->faceColor[5][2] = m_pCuboidSet->m_RIGHT_BLUE;

		m_pModel->addFigure(static_cast<Figure*>(pCuboid));
		m_pCuboidSet->MoveNext();
	}
}


void FigureDatabaseEditor::saveEllipsoidDB()
{
	if (!m_pEllipsoidSet->IsBOF())
		m_pEllipsoidSet->MoveFirst();

	// deleting old records
	while (!m_pEllipsoidSet->IsEOF())
	{
		m_pEllipsoidSet->Delete();
		m_pEllipsoidSet->MoveNext();
	}
	m_pEllipsoidSet->Requery();

	// writing new records
	for (auto it = m_pModel->m_Figures.begin(); it != m_pModel->m_Figures.end(); ++it)
	if (typeid(*(*it)) == typeid(Ellipsoid))
	{
		Ellipsoid* pEllipsoid = dynamic_cast<Ellipsoid*>(*it);
		m_pEllipsoidSet->AddNew();

		m_pEllipsoidSet->m_A = pEllipsoid->a;
		m_pEllipsoidSet->m_B = pEllipsoid->b;
		m_pEllipsoidSet->m_C = pEllipsoid->c;
		m_pEllipsoidSet->m_MOVE_X = pEllipsoid->moveX;
		m_pEllipsoidSet->m_MOVE_Y = pEllipsoid->moveY;
		m_pEllipsoidSet->m_MOVE_Z = pEllipsoid->moveZ;
		m_pEllipsoidSet->m_ROTATE_X = pEllipsoid->rotateX;
		m_pEllipsoidSet->m_ROTATE_Y = pEllipsoid->rotateY;
		m_pEllipsoidSet->m_ROTATE_Z = pEllipsoid->rotateZ;
		m_pEllipsoidSet->m_ZOOM = pEllipsoid->zoom;
		m_pEllipsoidSet->m_COLOR_RED = pEllipsoid->color[0];
		m_pEllipsoidSet->m_COLOR_GREEN = pEllipsoid->color[1];
		m_pEllipsoidSet->m_COLOR_BLUE = pEllipsoid->color[2];

		if (m_pEllipsoidSet->CanUpdate())
			m_pEllipsoidSet->Update();
		m_pEllipsoidSet->Requery();
	}
}


void FigureDatabaseEditor::loadEllipsoidDB()
{
	if (!m_pEllipsoidSet->IsBOF())
		m_pEllipsoidSet->MoveFirst();

	while (!m_pEllipsoidSet->IsEOF())
	{
		Ellipsoid* pEllipsoid = new Ellipsoid;

		pEllipsoid->a = m_pEllipsoidSet->m_A;
		pEllipsoid->b = m_pEllipsoidSet->m_B;
		pEllipsoid->c = m_pEllipsoidSet->m_C;
		pEllipsoid->moveX = m_pEllipsoidSet->m_MOVE_X;
		pEllipsoid->moveY = m_pEllipsoidSet->m_MOVE_Y;
		pEllipsoid->moveZ = m_pEllipsoidSet->m_MOVE_Z;
		pEllipsoid->rotateX = m_pEllipsoidSet->m_ROTATE_X;
		pEllipsoid->rotateY = m_pEllipsoidSet->m_ROTATE_Y;
		pEllipsoid->rotateZ = m_pEllipsoidSet->m_ROTATE_Z;
		pEllipsoid->zoom = m_pEllipsoidSet->m_ZOOM;
		pEllipsoid->color[0] = m_pEllipsoidSet->m_COLOR_RED;
		pEllipsoid->color[1] = m_pEllipsoidSet->m_COLOR_GREEN;
		pEllipsoid->color[2] = m_pEllipsoidSet->m_COLOR_BLUE;

		m_pModel->addFigure(static_cast<Figure*>(pEllipsoid));
		m_pEllipsoidSet->MoveNext();
	}
}
