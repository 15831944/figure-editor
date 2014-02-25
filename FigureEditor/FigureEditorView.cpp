
// FigureEditorView.cpp : implementation of the CFigureEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FigureEditor.h"
#endif

#include "FigureEditorView.h"
#include "CuboidDlg.h"
#include "EllipsoidDlg.h"
#include "ProjectionsDlg.h"
#include "RotationDlg.h"
#include "ColorDlg.h"
#include "CuboidColorDlg.h"
#include "Matrix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFigureEditorView

IMPLEMENT_DYNCREATE(CFigureEditorView, CRecordView)

BEGIN_MESSAGE_MAP(CFigureEditorView, CRecordView)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDCUBOID, &CFigureEditorView::OnAddcuboid)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CHANGECOLOR, &CFigureEditorView::OnChangeColor)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_ADDELLIPSOID, &CFigureEditorView::OnAddEllipsoid)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_EDIT_DRAWPROJECTION, &CFigureEditorView::OnDrawprojection)
	ON_COMMAND(ID_EDIT_DELETE, &CFigureEditorView::OnDelete)
	ON_COMMAND(ID_EDIT_ROTATE, &CFigureEditorView::OnRotate)
	ON_COMMAND(ID_FILE_SAVETODATABASE, &CFigureEditorView::OnFileSavetodatabase)
	ON_COMMAND(ID_FILE_LOADFROMDATABASE, &CFigureEditorView::OnLoadFromDatabase)
	ON_COMMAND(ID_EDIT_CHANGEFACECOLOR, &CFigureEditorView::OnChangeFaceColor)
END_MESSAGE_MAP()

// CFigureEditorView construction/destruction

CFigureEditorView::CFigureEditorView()
	: CRecordView(CFigureEditorView::IDD)
{
	angleX = +3.0;
	angleY = -4.0;
	zoomZ = -12.2;
	light = true;
	menu = false;
	// TODO: add construction code here

}

CFigureEditorView::~CFigureEditorView()
{
	delete controller;
	delete model;
}

void CFigureEditorView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information
}

BOOL CFigureEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CFigureEditorView::OnInitialUpdate()
{
	model = new FigureSet;
	model->attach(static_cast<IObserver*>(this)); // subscribe for model updates
	new FigureDatabaseEditor(model, &GetDocument()->m_CuboidSet, &GetDocument()->m_EllipsoidSet);
	controller = new StandardController(model); // choose standard controller
	
	CRecordView::OnInitialUpdate();
}


// CFigureEditorView diagnostics

#ifdef _DEBUG
void CFigureEditorView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CFigureEditorView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CFigureEditorDoc* CFigureEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFigureEditorDoc)));
	return (CFigureEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CFigureEditorView database support
CRecordset* CFigureEditorView::OnGetRecordset()
{
	return &GetDocument()->m_EllipsoidSet;
}

// drawing functions
void CFigureEditorView::getHGLRC(HWND hWnd)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR), // struct size 
		1,                              // Version number
		PFD_DRAW_TO_WINDOW |    // Flags, draw to a window,
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,          // RGBA pixel values
		24,                     // 24-bit color
		0, 0, 0,                // RGB bits & shift sizes.
		0, 0, 0,                // Don't care about them
		0, 0,                   // No alpha buffer info
		0, 0, 0, 0, 0,          // No accumulation buffer
		32,                     // 32-bit depth buffer
		0,                      // No stencil buffer
		0,                      // No auxiliary buffers
		PFD_MAIN_PLANE,         // Layer type
		0,                      // Reserved (must be 0)
		0,                      // No layer mask
		0,                      // No visible mask
		0                       // No damage mask
	};


	HDC hdc = ::GetDC(hWnd);
	int nMyPixelFormatID = ChoosePixelFormat(hdc, &pfd);
	if (!nMyPixelFormatID)
	{
		MessageBox(_T("May be you do not install OpenGL!"), _T("Error!"), MB_ICONERROR | MB_OK);
		exit(1);
	}
	if (!SetPixelFormat(hdc, nMyPixelFormatID, &pfd))
	{
		MessageBox(_T("Can not set pixel format for OpenGL!"), _T("Error!"), MB_ICONERROR | MB_OK);
		exit(1);
	}

	glCullFace(GL_BACK);

	m_hrc = wglCreateContext(hdc);
	//wglMakeCurrent(m_hdc, m_hrc);
}

void CFigureEditorView::lightInit()
{
	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -5.0, 3.0, 7.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	GLfloat mat_emission[] = { 0, 0, 0, 1 };
	//GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
}

void CFigureEditorView::graphicsInit()
{	
	// rendering options
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);								// Normalization
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CFigureEditorView::drawAxes()
{
	glDisable(GL_LIGHTING);
	glLineWidth(1);
	glColor3d(1.0, 0.0, 0.0);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3d(-10, 0, 0);
	glVertex3d(10, 0, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3d(10, 0.2, 0);
	glVertex3d(10.2, 0, 0);
	glVertex3d(10, -0.2, 0);
	glEnd();
	glColor3d(0.0, 1.0, 0.0);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3d(0, -10, 0);
	glVertex3d(0, 10, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3d(-0.2, 10, 0);
	glVertex3d(0, 10.2, 0);
	glVertex3d(+0.2, 10, 0);
	glEnd();
	glColor3d(0.0, 0.0, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3d(0, 0, -10);
	glVertex3d(0, 0, 10);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3d(-0.2, 0, 10);
	glVertex3d(0, 0, 10.2);
	glVertex3d(+0.2, 0, 10);
	glEnd();
	glColor4d(1.0, 1.0, 1.0, 1.0);
	if (light) glEnable(GL_LIGHTING);
}

void CFigureEditorView::drawFigures(GLenum mode)
{
	if (!model) return;
	if (mode == GL_SELECT){
		int size = model->m_Figures.size();
		for (int i = 0; i < size; ++i){
			glPushName(i);
			drawFigure(model->m_Figures[i]);
			glPopName();
		}
		for (int i = 0; i < size; ++i)
		if (model->m_Figures[i]->projectedXOY || model->m_Figures[i]->projectedYOZ || model->m_Figures[i]->projectedXOZ)
		{
			drawProjection(model->m_Figures[i]);
		}
	}
	else{
		int size = model->m_Figures.size();
		for (int i = 0; i < size; ++i){
			drawFigure(model->m_Figures[i]);
			if (model->m_Figures[i]->projectedXOY || model->m_Figures[i]->projectedYOZ || model->m_Figures[i]->projectedXOZ)
				drawProjection(model->m_Figures[i]);
		}
	}
}

void CFigureEditorView::drawFigure(Figure* figure)
{
	if (typeid(*figure) == typeid(Cuboid))
		drawCuboid(dynamic_cast<Cuboid*>(figure));
	else if (typeid(*figure) == typeid(Ellipsoid))
		drawEllipsoid(dynamic_cast<Ellipsoid*>(figure));
}

void CFigureEditorView::drawCuboid(Cuboid* cuboid)
{
	glPushMatrix();
	glTranslatef(cuboid->moveX, cuboid->moveY, cuboid->moveZ);
	glRotatef(cuboid->rotateX, 1.0, 0.0, 0.0);
	glRotatef(cuboid->rotateY, 0.0, 1.0, 0.0);
	glRotatef(cuboid->rotateZ, 0.0, 0.0, 1.0);
	glScaled(cuboid->zoom, cuboid->zoom, cuboid->zoom);

	GLfloat normalv[][3] = 
		{/*top*/{ 0.0, 1.0, 0.0 },
		/*bottom*/{ 0.0, -1.0, 0.0 },
		/*front*/{ 0.0, 0.0, 1.0 },
		/*back*/{ 0.0, 0.0, -1.0 },
		/*left*/{ -1.0, 0.0, 0.0 },
		/*right*/{ 1.0, 0.0, 0.0 } };

	double coord[6][4][3] = 
	{/*top*/{ { -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 }, 
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 } },
	/*bottom*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 }, 
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 }, 
			{ -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } },
	/*front*/{ { -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 } },
	/*back*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 } },
	/*left*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } },
	/*right*/{ { cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } } };

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i) {
		if (cuboid->intersected)
			glColor4f(1.0, 0.0, 0.0, cuboid->visibility);
		else
			glColor4f(cuboid->faceColor[i][0] / 255.0, cuboid->faceColor[i][1] / 255.0, cuboid->faceColor[i][2] / 255.0, cuboid->visibility);
		glNormal3f(normalv[i][0], normalv[i][1], normalv[i][2]);
		for (int j = 0; j < 4; ++j) {
			glVertex3f(coord[i][j][0], coord[i][j][1], coord[i][j][2]);
		}
	}
	glEnd();
	glPopMatrix();
}

void CFigureEditorView::drawEllipsoid(Ellipsoid* ellipsoid)
{
	glPushMatrix();
	glTranslatef(ellipsoid->moveX, ellipsoid->moveY, ellipsoid->moveZ);
	glRotatef(ellipsoid->rotateX, 1.0, 0.0, 0.0);
	glRotatef(ellipsoid->rotateY, 0.0, 1.0, 0.0);
	glRotatef(ellipsoid->rotateZ, 0.0, 0.0, 1.0);
	glScaled(ellipsoid->zoom*ellipsoid->a, ellipsoid->zoom*ellipsoid->b, ellipsoid->zoom*ellipsoid->c);
	if (ellipsoid->intersected)
		glColor4f(1.0, 0.0, 0.0, ellipsoid->visibility);
	else
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, ellipsoid->visibility);
	gluSphere(ellipsoid->quadricObj, 1.0, 64, 64);
	glPopMatrix();
}

void CFigureEditorView::drawProjection(Figure* figure)
{
	if (typeid(*figure) == typeid(Cuboid))
		drawCuboidProjection(dynamic_cast<Cuboid*>(figure));
	else if (typeid(*figure) == typeid(Ellipsoid))
		drawEllipsoidProjection(dynamic_cast<Ellipsoid*>(figure));
}

void CFigureEditorView::drawCuboidProjection(Cuboid* cuboid)
{
	double coord[6][4][3] =
	{/*top*/{ { -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 } },
	/*bottom*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } },
	/*front*/{ { -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 } },
	/*back*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 } },
	/*left*/{ { -cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ -cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ -cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } },
	/*right*/{ { cuboid->length / 2, -cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, -cuboid->width / 2 },
			{ cuboid->length / 2, cuboid->height / 2, cuboid->width / 2 },
			{ cuboid->length / 2, -cuboid->height / 2, cuboid->width / 2 } } };

	double color[] = { 0.0, 0.0, 0.0 };
	for (int i = 0; i < 6; i++)
	{
		color[0] += cuboid->faceColor[i][0] / 6.0 / 255.0;
		color[1] += cuboid->faceColor[i][1] / 6.0 / 255.0;
		color[2] += cuboid->faceColor[i][2] / 6.0 / 255.0;
	}

	Matrix rotation(3);
	rotation.getRotation(cuboid->rotateX / 180.0 * M_PI, -cuboid->rotateY / 180.0 * M_PI, cuboid->rotateZ / 180.0 * M_PI);

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 4; j++)
		rotation * coord[i][j];

	if (cuboid->projectedXOY)
	{
		glPushMatrix();
		glTranslated(cuboid->moveX, cuboid->moveY, 0.0);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor3d(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				glVertex3f(coord[i][j][0], coord[i][j][1], 0.0);
			}
		}
		glEnd();
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	if (cuboid->projectedYOZ)
	{
		glPushMatrix();
		glTranslated(0.0, cuboid->moveY, cuboid->moveZ);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor3d(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				glVertex3f(0.0, coord[i][j][1], coord[i][j][2]);
			}
		}
		glEnd();
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	if (cuboid->projectedXOZ)
	{
		glPushMatrix();
		glTranslated(cuboid->moveX, 0.0, cuboid->moveZ);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor3d(color[0], color[1], color[2]);
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 4; ++j) {
				glVertex3f(coord[i][j][0], 0.0, coord[i][j][2]);
			}
		}
		glEnd();
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}

void CFigureEditorView::drawEllipsoidProjection(Ellipsoid* ellipsoid)
{
	const double GrToR = M_PI / 180.0;
	/*if (ellipsoid->projectedXOY)
	{
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);

		vector<double> point(3);
		Matrix rotation(3);
		rotation.getRotation(ellipsoid->rotateX / 180.0 * M_PI, -ellipsoid->rotateY / 180.0 * M_PI, ellipsoid->rotateZ / 180.0 * M_PI);

		for (double theta = 0.0; theta < M_PI * 2; theta += 0.1)
		{
			glBegin(GL_POLYGON);
			for (double phi = -M_PI_2; phi <= M_PI_2; phi += 0.1)
			{
				point[0] = ellipsoid->a * sin(theta) * cos(phi);
				point[1] = ellipsoid->b * sin(theta) * sin(phi);
				point[2] = ellipsoid->c * cos(theta);

				point = rotation * point;

				point[0] += ellipsoid->moveX;
				point[1] += ellipsoid->moveY;
				point[2] += ellipsoid->moveZ;

				glVertex3f(point[0], point[1], 0.0);
			}
			glEnd();
		}
		if (light) glEnable(GL_LIGHTING);
	}
	if (ellipsoid->projectedYOZ)
	{
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);

		vector<double> point(3);
		Matrix rotation(3);
		rotation.getRotation(ellipsoid->rotateX / 180.0 * M_PI, -ellipsoid->rotateY / 180.0 * M_PI, ellipsoid->rotateZ / 180.0 * M_PI);

		for (double theta = 0.0; theta < M_PI * 2; theta += 0.1)
		{
			glBegin(GL_POLYGON);
			for (double phi = -M_PI_2; phi <= M_PI_2; phi += 0.1)
			{
				point[0] = ellipsoid->a * sin(theta) * cos(phi);
				point[1] = ellipsoid->b * sin(theta) * sin(phi);
				point[2] = ellipsoid->c * cos(theta);

				point = rotation * point;

				point[0] += ellipsoid->moveX;
				point[1] += ellipsoid->moveY;
				point[2] += ellipsoid->moveZ;

				glVertex3f(0.0, point[1], point[2]);
			}
			glEnd();
		}
		if (light) glEnable(GL_LIGHTING);
	}
	if (ellipsoid->projectedXOZ)
	{
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);

		vector<double> point(3);
		Matrix rotation(3);
		rotation.getRotation(ellipsoid->rotateX / 180.0 * M_PI, -ellipsoid->rotateY / 180.0 * M_PI, ellipsoid->rotateZ / 180.0 * M_PI);

		for (double theta = 0.0; theta < M_PI * 2; theta += 0.01)
		{
			glBegin(GL_POLYGON);
			for (double phi = -M_PI_2; phi <= M_PI_2; phi += 0.1)
			{
				point[0] = ellipsoid->a * sin(theta) * cos(phi);
				point[1] = ellipsoid->b * sin(theta) * sin(phi);
				point[2] = ellipsoid->c * cos(theta);

				point = rotation * point;

				point[0] += ellipsoid->moveX;
				point[1] += ellipsoid->moveY;
				point[2] += ellipsoid->moveZ;

				glVertex3f(point[0], 0.0, point[2]);
			}
			glEnd();
		}
		if (light) glEnable(GL_LIGHTING);
	}*/
	if (ellipsoid->projectedXOY)
	{
		glPushMatrix();
		glTranslated(ellipsoid->moveX, ellipsoid->moveY, 0.0);
		glRotatef(ellipsoid->rotateZ, 0.0, 0.0, 1.0);
		double newA = ellipsoid->a * cos(GrToR * ellipsoid->rotateY) * cos(GrToR * ellipsoid->rotateY) + ellipsoid->c * sin(GrToR * ellipsoid->rotateY) * sin(GrToR * ellipsoid->rotateY),
			newB = ellipsoid->b * cos(GrToR * ellipsoid->rotateX) * cos(GrToR * ellipsoid->rotateX) + ellipsoid->c * sin(GrToR * ellipsoid->rotateX) * sin(GrToR * ellipsoid->rotateX);
		glScaled(ellipsoid->zoom * newA, ellipsoid->zoom * newB, ellipsoid->zoom);
		glNormal3f(0.0, 0.0, 1.0);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);
		gluDisk(ellipsoid->quadricObj, 0.0, 1.0, 32, 32);
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	if (ellipsoid->projectedYOZ)
	{
		glPushMatrix();
		glRotated(-90.0, 0.0, 1.0, 0.0);
		glTranslated(ellipsoid->moveZ, ellipsoid->moveY, 0.0);
		glRotatef(-ellipsoid->rotateX, 0.0, 0.0, 1.0);
		double newC = ellipsoid->c * cos(GrToR * ellipsoid->rotateY) * cos(GrToR * ellipsoid->rotateY) + ellipsoid->a * sin(GrToR * ellipsoid->rotateY) * sin(GrToR * ellipsoid->rotateY),
			newB = ellipsoid->b * cos(GrToR * ellipsoid->rotateZ) * cos(GrToR * ellipsoid->rotateZ) + ellipsoid->a * sin(GrToR * ellipsoid->rotateZ) * sin(GrToR * ellipsoid->rotateZ);

		glScaled(ellipsoid->zoom * newC, ellipsoid->zoom * newB, ellipsoid->zoom);
		glNormal3f(-1.0, 0.0, 0.0);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);
		gluDisk(ellipsoid->quadricObj, 0.0, 1.0, 32, 32);
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	if (ellipsoid->projectedXOZ)
	{
		glPushMatrix();
		glRotated(90.0, 1.0, 0.0, 0.0);
		glTranslated(ellipsoid->moveX, ellipsoid->moveZ, 0.0);
		double sign = cos(GrToR * ellipsoid->rotateX) + 0.001;
		glRotatef(-cos(GrToR * ellipsoid->rotateX)*ellipsoid->rotateY, 0.0, 0.0, 1.0);
		//double newA = ellipsoid->a * cos(GrToR * ellipsoid->rotateZ) * cos(GrToR * ellipsoid->rotateZ) + ellipsoid->b * sin(GrToR * ellipsoid->rotateZ) * sin(GrToR * ellipsoid->rotateZ),
			//newC = ellipsoid->c * cos(GrToR * ellipsoid->rotateX) * cos(GrToR * ellipsoid->rotateX) + ellipsoid->b * sin(GrToR * ellipsoid->rotateX) * sin(GrToR * ellipsoid->rotateX);
		double newA = max(abs(ellipsoid->a * cos(GrToR * ellipsoid->rotateZ)), abs(ellipsoid->b * sin(GrToR * ellipsoid->rotateZ))),
			newC = max(abs(ellipsoid->c * cos(GrToR * ellipsoid->rotateX)), abs(ellipsoid->b * sin(GrToR * ellipsoid->rotateX)));
		glScaled(ellipsoid->zoom * newA, ellipsoid->zoom * newC, ellipsoid->zoom);
		glNormal3f(0.0, -1.0, 0.0);
		GLboolean light(0);
		glGetBooleanv(GL_LIGHTING, &light);
		glDisable(GL_LIGHTING);
		glColor4f(ellipsoid->color[0] / 255.0, ellipsoid->color[1] / 255.0, ellipsoid->color[2] / 255.0, 1.0);
		gluDisk(ellipsoid->quadricObj, 0.0, 1.0, 32, 32);
		if (light) glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}


// CFigureEditorView message handlers

int CFigureEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRecordView::OnCreate(lpCreateStruct) == -1)
		return -1;

	getHGLRC(m_hWnd);
	return 0;
}

void CFigureEditorView::OnDestroy()
{
	CRecordView::OnDestroy();
}

void CFigureEditorView::OnSize(UINT nType, int cx, int cy)
{
	CRecordView::OnSize(nType, cx, cy);
	HDC hDC = ::GetDC(this->m_hWnd);
	wglMakeCurrent(hDC, m_hrc);

	glnWidth = (GLsizei)cx;
	glnHeight = (GLsizei)cy;
	gldAspect = (GLdouble)glnWidth / (GLdouble)glnHeight;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, glnWidth, glnHeight);
	gluPerspective(45.0, gldAspect, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();	

	lightInit();
	graphicsInit();

	// Reset The Modelview Matrix
	wglMakeCurrent(NULL, NULL);
	::ReleaseDC(this->m_hWnd, hDC);
}

void CFigureEditorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	wglMakeCurrent(dc.m_hDC, m_hrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f, 0.0f, zoomZ);						// zoom
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);					// turn left/right
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);					// rurn up/down

	// set up lighting
	if (light)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	drawAxes();
	drawFigures(GL_RENDER);

	SwapBuffers(dc.m_hDC);
	wglMakeCurrent(NULL, NULL);
}

BOOL CFigureEditorView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CFigureEditorView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if (menu && model && model->getSelectedFiguresNumber())
	{
		CMenu menu;
		menu.LoadMenu(IDR_CONTEXTMENU);
		CMenu* submenu = menu.GetSubMenu(0);
		ASSERT(submenu);
		int index;
		if (model->getSelectedFiguresNumber() != 1 || typeid(*(model->getSelectedFigure(index))) != typeid(Cuboid))
			submenu->EnableMenuItem(ID_EDIT_CHANGEFACECOLOR, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		submenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

void CFigureEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'a':
	case 'A':
		angleY -= 2.5f;
		RedrawWindow();
		break;
	case 'd':
	case 'D':
		angleY += 2.5f;
		RedrawWindow();
		break;
	case 'w':
	case 'W':
		angleX += 2.5f;
		RedrawWindow();
		break;
	case 's':
	case 'S':
		angleX -= 2.5f;
		RedrawWindow();
		break;
	case VK_OEM_PLUS:
		zoomZ += 0.1f;
		RedrawWindow();
		break;
	case VK_OEM_MINUS:
		zoomZ -= 0.1f;
		RedrawWindow();
		break;
	case 'l':
	case 'L':
		light = !light;
		RedrawWindow();
		break;
	case VK_ESCAPE:
		exit(0);
		break;
	}

	CRecordView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFigureEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (model && controller)
	{
		const int BUFSIZE = 512;
		GLuint selectBuf[BUFSIZE];			//buffer of figures names(indexs in m_Figures[])
		GLint hits;							//1 if picked the figure
		GLint viewport[4];

		HDC hDC = ::GetDC(this->m_hWnd);
		wglMakeCurrent(hDC, m_hrc);

		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer(BUFSIZE, selectBuf);

		glRenderMode(GL_SELECT);				// Enter the SELECT render mode
		glInitNames();
		glPushName(-1);							//space gets name -1

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix((GLdouble)point.x, (GLdouble)(viewport[3] - point.y),
			5.0, 5.0, viewport);
		gluPerspective(45.0, gldAspect, 0.1, 100.0);
		glMatrixMode(GL_MODELVIEW);

		drawFigures(GL_SELECT);					//redraw scene using names for figures
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glFlush();

		hits = glRenderMode(GL_RENDER);
		const int NO_FIGURES_PICKED = -1;

		if (hits)
			controller->DoubleClickOnFigure(nFlags, selectBuf[4]);
		else
			controller->DoubleClickOnFigure(nFlags, NO_FIGURES_PICKED);
		wglMakeCurrent(NULL, NULL);
		::ReleaseDC(this->m_hWnd, hDC);
	}
	CRecordView::OnLButtonDblClk(nFlags, point);
}

void CFigureEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (controller)
		controller->LButtonDown(nFlags, point);
	CRecordView::OnLButtonDown(nFlags, point);
}

void CFigureEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (controller)
		controller->RButtonDown(nFlags, point);
	menu = true;
	CRecordView::OnRButtonDown(nFlags, point);
}

void CFigureEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (controller)
		controller->MouseMove(nFlags, point);
	menu = false;
	CRecordView::OnMouseMove(nFlags, point);
}

BOOL CFigureEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (controller)
		controller->MouseWheel(nFlags, zDelta, pt);
	menu = false;
	return CRecordView::OnMouseWheel(nFlags, zDelta, pt);
}

void CFigureEditorView::OnAddcuboid()
{
	CCuboidDlg dlg;
	dlg.DoModal();
	if (dlg.pOut && controller)
		controller->AddCuboid(dlg.pOut);
}

void CFigureEditorView::OnAddEllipsoid()
{
	CEllipsoidDlg dlg;
	dlg.DoModal();
	if (dlg.pOut && controller)
		controller->AddEllipsoid(dlg.pOut);
}

void CFigureEditorView::OnChangeColor()
{
	CColorDlg dlg;
	INT_PTR nRet = dlg.DoModal();
	if (nRet == IDOK && controller)
		controller->ChangeColor(dlg.red, dlg.green, dlg.blue);
}

void CFigureEditorView::OnChangeFaceColor()
{
	if (!controller) return;

	if (model->getSelectedFiguresNumber() == 1)
	{
		int index(0);
		Figure *f = model->getSelectedFigure(index);
		if (typeid(*f) == typeid(Cuboid))
		{
			Cuboid* pCuboid = dynamic_cast<Cuboid*>(f);
			CCuboidColorDlg dlg(pCuboid);
			dlg.DoModal();
			if (dlg.pOut)
			{
				Figure* recolouredCuboid = static_cast<Figure*>(dlg.pOut);
				controller->UpdateFigure(index, recolouredCuboid);
			}
		}
	}
}


void CFigureEditorView::OnDrawprojection()
{
	CProjectionsDlg dlg;
	INT_PTR nRet = dlg.DoModal();
	if (nRet == IDOK && controller)
		controller->Project(dlg.xoy, dlg.yoz, dlg.xoz);
}

void CFigureEditorView::OnDelete()
{
	if (controller)
		controller->Delete();
}

void CFigureEditorView::OnRotate()
{
	CRotationDlg dlg(this);
	INT_PTR nRet = dlg.DoModal();
	if (nRet == IDOK && controller)
		controller->Rotate(dlg.m_Angle, dlg.Ox, dlg.Oy, dlg.Oz);
}

void CFigureEditorView::OnFileSavetodatabase()
{
	if (controller)
		controller->SaveDatabase();
}


void CFigureEditorView::OnLoadFromDatabase()
{
	if (controller)
		controller->LoadDatabase();
}

void CFigureEditorView::update()
{
	RedrawWindow();
}

