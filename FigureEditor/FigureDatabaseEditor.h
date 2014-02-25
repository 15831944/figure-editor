#pragma once
#include "FigureSet.h"
#include "CuboidSet.h"
#include "EllipsoidSet.h"

class FigureDatabaseEditor
{
protected:
	FigureSet* m_pModel;
	CCuboidSet* m_pCuboidSet;
	CEllipsoidSet* m_pEllipsoidSet;
public:
	FigureDatabaseEditor(FigureSet* model, CCuboidSet* pCuboidSet, CEllipsoidSet* pEllipsoidSet);
	virtual ~FigureDatabaseEditor();
	virtual void saveDatabase();
	virtual void loadDatabase();
protected:
	void saveCuboidDB();
	void loadCuboidDB();
	void saveEllipsoidDB();
	void loadEllipsoidDB();
};