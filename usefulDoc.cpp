
// usefulDoc.cpp : CusefulDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "useful.h"
#endif

#include "usefulDoc.h"
#include "MnistPredictDlg.h"
#include "Dialog3D.h"

#include "shpEngine/GeoPoint.h"
#include "shpEngine/GeoPolyline.h"
#include "shpEngine/GeoPolygon.h"

#include <propkey.h>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CusefulDoc
IMPLEMENT_DYNCREATE(CusefulDoc, CDocument)
BEGIN_MESSAGE_MAP(CusefulDoc, CDocument)
	ON_COMMAND(ID_32771, &CusefulDoc::OnBPNet)
	ON_COMMAND(ID_32772, &CusefulDoc::OnLoadTriangle)
	ON_COMMAND(ID_32773, &CusefulDoc::OnLoadGrid)
	ON_COMMAND(ID_32774, &CusefulDoc::On3DView)
	ON_COMMAND(ID_32780, &CusefulDoc::OnClear)
	ON_COMMAND(ID_SHP32777, &CusefulDoc::OnShpClear)
END_MESSAGE_MAP()

// CusefulDoc ����/����
CusefulDoc::CusefulDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_triShow =FALSE;
	m_gridShow=FALSE;
	m_shp_Show=FALSE;
	m_pDataSource = new DataSource() ;
}
CusefulDoc::~CusefulDoc()
{
	if ( m_pDataSource != 0 )
	{
		delete m_pDataSource ;
		m_pDataSource = 0 ;
	}
}
BOOL CusefulDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// CusefulDoc ���л�
void CusefulDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#ifdef SHARED_HANDLERS
// ����ͼ��֧��
void CusefulDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}
// ������������֧��
void CusefulDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}
void CusefulDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}
#endif // SHARED_HANDLERS

// CusefulDoc ���
#ifdef _DEBUG
void CusefulDoc::AssertValid() const
{
	CDocument::AssertValid();
}
void CusefulDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

//���ļ��е��������Σ����������δ���
void CusefulDoc::load_triangle_file(tagTIN &tinNet,tagVEX &triVex,const char* pathFile)
{
	int triNumber,nfaces;
	char cnstTmpchar[2048];
	ifstream ifs(pathFile,ios_base::in);
	ifs.getline(cnstTmpchar,2048);
	ifs.getline(cnstTmpchar,2048);
	ifs.getline(cnstTmpchar,2048);
	triNumber=atoi(cnstTmpchar);
	TriVERTIX pdfTriVex;
	for (int i=0;i<triNumber;i++)
	{
		ifs.getline(cnstTmpchar,2048);
		int indexnum;
		sscanf(cnstTmpchar,"%d%lf%lf",&indexnum,&pdfTriVex.padivertixX,&pdfTriVex.padivertixY);
		triVex.push_back(pdfTriVex);
	}

	ifs.getline(cnstTmpchar,2048);
	ifs.getline(cnstTmpchar,2048);
	ifs.getline(cnstTmpchar,2048);
	nfaces=atoi(cnstTmpchar);
	TRIANGLE m_tri;
	for (int i=0;i<nfaces;i++)
	{
		ifs.getline(cnstTmpchar,2048);
		sscanf(cnstTmpchar,"%d%d%d%d%d%d",&m_tri.paivertix[0],&m_tri.paivertix[1],&m_tri.paivertix[2],
										  &m_tri.piffacest[0],&m_tri.piffacest[1],&m_tri.piffacest[2]);
		tinNet.push_back(m_tri);
	}
	m_shp_Show=FALSE;
	m_triShow=TRUE;
	m_gridShow=FALSE;
	ifs.close();
}
void CusefulDoc::load_grid_file(tagGRID &grid,const char* pathFile)
{
	char cnstTmpchar[2048];
	ifstream ifs(pathFile,ios_base::in);
	ifs.getline(cnstTmpchar,2048);
	do 
	{
		ifs.getline(cnstTmpchar,2048);
		GridVERTIX gridVertix;
		sscanf(cnstTmpchar,"%lf,%lf,%lf",&gridVertix.grid_x,&gridVertix.grid_y,&gridVertix.grid_value);
		grid.push_back(gridVertix);
	} while (!ifs.eof());
	m_shp_Show=FALSE;
	m_triShow=FALSE;
	m_gridShow=TRUE;
}

FeatureClass* CusefulDoc::load_shapefile_file() 
{
	// TODO: Add your command handler code here

	static char BASED_CODE szFilter[] = "Data Files (*.shp)|*.shp|All Files (*.*)|*.*||" ;
	CFileDialog dlg( true , NULL , NULL , OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , szFilter , NULL ) ;
	if( dlg.DoModal() == IDCANCEL )
	{
		AfxMessageBox( "��û��ѡ��Ҫ�򿪵��ļ�!" ) ;
		return 0;
	}

	CString pathName = dlg.GetPathName() ;
	CString dbfFileName = pathName	;
	CString fileExt = dlg.GetFileExt();
	dbfFileName.Replace( "shp" , "dbf" );
	m_dbfPath.push_back(dbfFileName);
	layerName = dlg.GetFileTitle() ;
	m_shpPath.push_back(layerName);

	fileExt.MakeUpper();
	if( fileExt == "SHP")
	{
		FILE* fpShp = fopen( pathName , "rb" ) ;
		FILE* fpDbf = fopen( dbfFileName , "rb" ) ;

		if( fpShp==NULL )
		{
			AfxMessageBox( "���ļ�ʧ��!" ) ;
			return 0;
		}
		if( fpDbf ==NULL)
		{
			AfxMessageBox( "�������ļ�ʧ��!" ) ;
			return 0;
		}
		FeatureClass *pFeatureClass = ImportShapeFileData( fpShp, fpDbf ) ;
		if ( pFeatureClass != 0 )
			pFeatureClass->CalculateBound();
		//�ر��ļ�
		fclose(fpShp) ;
		fpShp = 0 ;
		fclose(fpDbf);
		fpDbf = 0 ;

		m_shp_Show=TRUE;
		m_triShow=FALSE;
		m_gridShow=FALSE;
		return pFeatureClass ;
	}

	return 0 ;
}
FeatureClass* CusefulDoc::ImportShapeFileData( FILE* fpShp, FILE* fpDbf )
{
	//��Shp�ļ�ͷ��ʼ
	int fileCode = -1;
	int fileLength = -1;
	int version = -1;
	int shapeType = -1;
	fread(&fileCode , sizeof(int) , 1 , fpShp) ;
	fileCode = ReverseBytes(fileCode) ;

	if (fileCode != 9994)
	{
		CString strTemp ;
		strTemp.Format(" WARNING filecode %d ", fileCode );
		AfxMessageBox(strTemp);
	}

	for( int i = 0 ; i < 5 ; i ++ )
		fread(&fileCode , sizeof(int) , 1 , fpShp) ;

	fread(&fileLength , sizeof(int) , 1 , fpShp) ;
	fileLength = ReverseBytes(fileLength) ;

	fread(&version , sizeof(int) , 1 , fpShp) ;
	fread(&shapeType , sizeof(int) , 1 , fpShp) ;

	double tempOriginX , tempOriginY ;
	fread( &tempOriginX , sizeof(double) , 1 , fpShp ) ;
	fread( &tempOriginY , sizeof(double) , 1 , fpShp ) ;

	double xMaxLayer , yMaxLayer ;
	fread( &xMaxLayer , sizeof(double) , 1 , fpShp ) ;
	fread( &yMaxLayer , sizeof(double) , 1 , fpShp ) ;

	double* skip = new double[4] ;
	fread( skip , sizeof(double) , 4 , fpShp ) ;
	delete []skip ;
	skip = 0 ;
	//��Shp�ļ�ͷ����

	int uniqueID = this->m_pDataSource->GetUniqueID() ;
	FeatureClass* pShpDataSet = 0 ;
	//����Ŀ�����ʹ�����Ӧ��ͼ��DataSet��
	switch( shapeType )
	{
	case 1 :
		pShpDataSet = (FeatureClass*)&(m_pDataSource->CreateDataSet(uniqueID , POINTDATASET , layerName)) ;
		break ;
	case 3 :
	case 23 :
		pShpDataSet = (FeatureClass*)&(m_pDataSource->CreateDataSet(uniqueID , LINEDATASET , layerName)) ;
		break ;
	case 5 :
		pShpDataSet = (FeatureClass*)&(m_pDataSource->CreateDataSet(uniqueID , POLYGONDATASET , layerName)) ;
		break ;
	}

	if ( pShpDataSet == 0 ) return 0;

	// ��DBF�ļ�ͷ---------begin------------
	struct DBFHeader
	{
		char m_nValid;
		char m_aDate[3];
		char m_nNumRecords[4];
		char m_nHeaderBytes[2];
		char m_nRecordBytes[2];
		char m_nReserved1[3];
		char m_nReserved2[13];
		char m_nReserved3[4];
	}dbfheader;

	struct DBFFIELDDescriptor
	{
		char m_sName[10];//Ӧ��Ϊchar m_sName[11]
		char m_nType;
		char m_nAddress[4];
		char m_nFieldLength;
		char m_nFieldDecimal;
		char m_nReserved1[2];
		char m_nWorkArea;
		char m_nReserved2[2];
		char m_nSetFieldsFlag;
		char m_nReserved3[8];
	};

	fread(&dbfheader,sizeof(DBFHeader),1,fpDbf);
	Fields& fields = pShpDataSet->GetFields();
	DBFFIELDDescriptor field ;
	BYTE endByte = ' ';
	char fieldName[12];
	int fieldDecimal, fieldLen, everyRecordLen = 0 ;
	while ( !feof(fpDbf) )
	{
		fread(&endByte,sizeof(BYTE),1,fpDbf);
		if ( endByte == 0x0D)	break ;
		fread(&field,sizeof(DBFFIELDDescriptor),1,fpDbf);

		fieldName[0] = endByte;
		for (int i = 0; i < 10; i ++ )
			fieldName[i+1] = field.m_sName[i];
		fieldName[11] = '\0';

		fieldDecimal = field.m_nFieldDecimal;
		fieldLen = field.m_nFieldLength;
		switch( field.m_nType )
		{
		case 'C':
			fields.AddField(fieldName,fieldName,FIELD_STRING,fieldLen);
			break;
		case 'F':
			fields.AddField(fieldName,fieldName,FIELD_DOUBLE,fieldLen);
			break;
		case 'N':
			{
				if ( fieldDecimal == 0 ) 
					fields.AddField(fieldName,fieldName,FIELD_INT,fieldLen);
				else fields.AddField(fieldName,fieldName,FIELD_DOUBLE,fieldLen);
			}
			break;
		}
		everyRecordLen += fieldLen ;
	}
	// ��DBF�ļ�ͷ---------end------------

	//��ȡshp��dbf�ļ�����-------start----------
	while( !feof(fpShp) )
	{
		//����¼ͷ��ʼ
		int recordNumber = -1 ;
		int contentLength = -1 ;
		fread(&recordNumber , sizeof(int) , 1 , fpShp) ;
		fread(&contentLength , sizeof(int) , 1 , fpShp) ;
		recordNumber = ReverseBytes(recordNumber) ;
		contentLength = ReverseBytes(contentLength) ;
		//����¼ͷ����
		switch( shapeType )
		{
		case 1: // '\001'
			//��ȡ��Ŀ�꿪ʼ
			{
				Fields &featureFields = pShpDataSet->GetFields();
				Feature *pFeature = new Feature(recordNumber , 1 , &featureFields) ;

				int pointShapeType ;
				fread(&pointShapeType , sizeof(int) , 1 , fpShp) ;
				double xValue , yValue ;
				fread(&xValue , sizeof(double) , 1 , fpShp) ;
				fread(&yValue , sizeof(double) , 1 , fpShp) ;

				GeoPoint *pNewGeoPoint = new GeoPoint( xValue , yValue ) ;
				pFeature->SetBound(xValue , yValue , 0 , 0 ) ;
				pFeature->SetGeometry(pNewGeoPoint) ;
				this->LoadAttributeData(pFeature,fpDbf,everyRecordLen);
				pShpDataSet->AddRow(pFeature) ;
			}
			break ;
			//��ȡ��Ŀ�����

		case 3: // '\003'
			//��ȡ��Ŀ�꿪ʼ
			{
				Fields &featureFields = pShpDataSet->GetFields();
				Feature *pFeature = new Feature(recordNumber , 1 , &featureFields) ;

				int arcShapeType ;
				fread(&arcShapeType , sizeof(int) , 1 , fpShp) ;

				double objMinX , objMinY , objMaxX , objMaxY ;
				fread(&objMinX , sizeof(double) , 1 , fpShp) ;
				fread(&objMinY , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxX , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxY , sizeof(double) , 1 , fpShp) ;

				GeoPolyline *pNewGeoLine = new GeoPolyline();
				double width = objMaxX - objMinX ;
				double height = objMaxY - objMinY ;
				pFeature->SetBound(objMinX , objMinY , width , height) ;

				int numParts , numPoints ;
				fread(&numParts , sizeof(int) , 1 , fpShp) ;
				fread(&numPoints , sizeof(int) , 1 , fpShp) ;
				//�洢�����ߵ��������
				int* startOfPart = new int[numParts] ;
				for( int i = 0 ; i < numParts ; i++ )
				{
					int indexFirstPoint ;
					fread(&indexFirstPoint , sizeof(int) , 1 , fpShp) ;
					startOfPart[i] = indexFirstPoint ;
				}

				//������Ŀ���ж����ߵ�����
				pNewGeoLine->SetPointsCount( numParts ) ;

				for(int i = 0 ; i < numParts ; i++ )
				{
					GeoPoints& points = pNewGeoLine->GetPoints(i) ;
					int curPosIndex = startOfPart[i] ;
					int nextPosIndex = 0 ;
					int curPointCount = 0 ;
					if( i == numParts - 1 )
						curPointCount = numPoints - curPosIndex ;
					else
					{
						nextPosIndex = startOfPart[i + 1] ;
						curPointCount = nextPosIndex - curPosIndex ;
					}
					points.SetPointCount( curPointCount ) ;
					//����һ���߶ε�����
					for( int iteratorPoint = 0 ; iteratorPoint < curPointCount ; iteratorPoint ++ )
					{
						double x , y ;
						fread(&x , sizeof(double) , 1 , fpShp) ;
						fread(&y , sizeof(double) , 1 , fpShp) ;
						GeoPoint newVertex(x, y);
						points.SetPoint(iteratorPoint, newVertex);
					}
				}
				delete []startOfPart ;
				startOfPart = 0 ;
				pFeature->SetGeometry(pNewGeoLine) ;
				this->LoadAttributeData(pFeature,fpDbf,everyRecordLen);
				pShpDataSet->AddRow(pFeature) ;
			}
			break ;
			//��ȡ��Ŀ�����

		case 5: // '\005'
			//��ȡ��Ŀ�꿪ʼ
			{
				Fields &featureFields = pShpDataSet->GetFields();
				Feature *pFeature = new Feature(recordNumber , 1 , &featureFields) ;
				int polygonShapeType ;
				fread(&polygonShapeType  , sizeof(int) , 1 ,fpShp) ;
				if( polygonShapeType != 5 )
					AfxMessageBox( "Error: Attempt to load non polygon shape as polygon." ) ;

				double objMinX , objMinY , objMaxX , objMaxY ;
				fread(&objMinX , sizeof(double) , 1 , fpShp) ;
				fread(&objMinY , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxX , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxY , sizeof(double) , 1 , fpShp) ;

				GeoPolygon *pNewGeoPolygon = new GeoPolygon();
				double width = objMaxX - objMinX ;
				double height = objMaxY - objMinY ;
				pFeature->SetBound(objMinX , objMinY , width , height) ;

				int numParts , numPoints ;
				fread(&numParts , sizeof(int) , 1 , fpShp) ;
				fread(&numPoints , sizeof(int) , 1 , fpShp) ;
				//�洢��������������
				int* startOfPart = new int[numParts] ;
				for( int i = 0 ; i < numParts ; i++ )
				{
					int indexFirstPoint ;
					fread(&indexFirstPoint , sizeof(int) , 1 , fpShp) ;
					startOfPart[i] = indexFirstPoint ;
				}

				//������Ŀ���ж�������
				pNewGeoPolygon->SetPointsCount( numParts ) ;

				for(int  i = 0 ; i < numParts ; i++ )
				{
					GeoPoints& points = pNewGeoPolygon->GetPoints(i) ;
					int curPosIndex = startOfPart[i] ;
					int nextPosIndex = 0 ;
					int curPointCount = 0 ;
					if( i == numParts - 1 )
						curPointCount = numPoints - curPosIndex ;
					else
					{
						nextPosIndex = startOfPart[i + 1];
						curPointCount = nextPosIndex - curPosIndex ;
					}
					points.SetPointCount( curPointCount ) ;
					//����һ����(�����)������
					for( int iteratorPoint = 0 ; iteratorPoint < curPointCount ; iteratorPoint ++ )
					{
						double x , y ;
						fread(&x , sizeof(double) , 1 , fpShp) ;
						fread(&y , sizeof(double) , 1 , fpShp) ;
						GeoPoint newVertex(x, y);
						points.SetPoint(iteratorPoint, newVertex);
					}
				}
				delete []startOfPart ;
				startOfPart = 0 ;
				pFeature->SetGeometry(pNewGeoPolygon) ;
				this->LoadAttributeData(pFeature,fpDbf,everyRecordLen);
				pShpDataSet->AddRow(pFeature) ;
			}
			break ;
			//��ȡ��Ŀ�����

		case 23: // '\027'
			//��ȡMeasure����Ŀ�꿪ʼ
			{
				Fields &featureFields = pShpDataSet->GetFields();
				Feature *pFeature = new Feature(recordNumber , 1 , &featureFields) ;
				int arcMShapeType ;
				fread(&arcMShapeType , sizeof(int) , 1 , fpShp) ;

				double objMinX , objMinY , objMaxX , objMaxY ;
				fread(&objMinX , sizeof(double) , 1 , fpShp) ;
				fread(&objMinY , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxX , sizeof(double) , 1 , fpShp) ;
				fread(&objMaxY , sizeof(double) , 1 , fpShp) ;

				GeoPolyline *pNewGeoLine = new GeoPolyline();
				double width = objMaxX - objMinX ;
				double height = objMaxY - objMinY ;
				pFeature->SetBound(objMinX , objMinY , width , height) ;

				int numParts , numPoints ;
				fread(&numParts , sizeof(int) , 1 , fpShp) ;
				fread(&numPoints , sizeof(int) , 1 , fpShp) ;
				//�洢�����ߵ��������
				int* startOfPart = new int[numParts] ;
				for( int i = 0 ; i < numParts ; i++ )
				{
					int indexFirstPoint ;
					fread(&indexFirstPoint , sizeof(int) , 1 , fpShp) ;
					startOfPart[i] = indexFirstPoint ;
				}

				//������Ŀ���ж����ߵ�����
				pNewGeoLine->SetPointsCount( numParts ) ;

				for(int  i = 0 ; i < numParts ; i++ )
				{
					GeoPoints& points = pNewGeoLine->GetPoints(i) ;
					int curPosIndex = startOfPart[i] ;
					int nextPosIndex = 0 ;
					int curPointCount = 0 ;
					if( i == numParts - 1 )
						curPointCount = numPoints - curPosIndex ;
					else
					{
						nextPosIndex = startOfPart[i + 1] ;
						curPointCount = nextPosIndex - curPosIndex ;
					}
					points.SetPointCount( curPointCount ) ;
					//����һ���߶ε�����
					for( int iteratorPoint = 0 ; iteratorPoint < curPointCount ; iteratorPoint ++ )
					{
						double x , y ;
						fread(&x , sizeof(double) , 1 , fpShp) ;
						fread(&y , sizeof(double) , 1 , fpShp) ;
						GeoPoint newVertex(x, y);
						points.SetPoint(iteratorPoint, newVertex);
					}
				}
				delete []startOfPart ;
				startOfPart = 0 ;

				double* value = new double[2 + numPoints] ;
				fread( value , sizeof(double) , 2+numPoints, fpShp) ;
				delete []value ;
				value = 0 ;

				pFeature->SetGeometry(pNewGeoLine) ;
				this->LoadAttributeData(pFeature,fpDbf,everyRecordLen);
				pShpDataSet->AddRow(pFeature);
			}
			break ;
			//��ȡMeasure����Ŀ�����
		}
	}
	return pShpDataSet ;
}
void CusefulDoc::LoadAttributeData(Feature *pFeature, FILE* fpDbf, int everyRecordLen)
{
	if ( everyRecordLen <= 0 ) return ;
	Fields &fields = pFeature->GetFields();
	int fieldCount = fields.Size();
	if ( fieldCount <= 0 ) return ;
	char *pValue = new char[everyRecordLen];
	fread( pValue, everyRecordLen*sizeof(char),1,fpDbf);
	int dPos = 1;
	for ( int j = 0; j < fieldCount; j ++ )
	{
		Field &field = fields.GetField(j);
		FieldValue &fieldvalue = pFeature->GetFieldValue(field.GetFieldName());
		int fieldType = field.GetFieldType();
		int fieldLen  = field.GetFieldLength();
		char *pfieldValue = new char[fieldLen+1];
		for ( int t = 0, k = dPos; k < dPos+fieldLen; k ++, t ++ )
			pfieldValue[t] = pValue[k];
		pfieldValue[fieldLen] = '\0';
		switch( fieldType )
		{
		case FIELD_STRING:
			fieldvalue.SetString( pfieldValue );
			break;
		case FIELD_DOUBLE:
			fieldvalue.SetDouble(atof(pfieldValue));
			break;
		case FIELD_INT:
			fieldvalue.SetInt( atoi(pfieldValue) );
			break;
		}
		delete []pfieldValue;
		dPos += fieldLen;
	}
	delete []pValue;
}
int CusefulDoc::ReverseBytes(int n)
{
	union
	{
		BYTE a[4];
		int n;
	} u,v;

	u.n = n;

	v.a[0] = u.a[3];
	v.a[1] = u.a[2];
	v.a[2] = u.a[1];
	v.a[3] = u.a[0];   

	return v.n;
}
DataSource& CusefulDoc::GetDataSource()
{
	return *m_pDataSource ;
}


// CusefulDoc ����
void CusefulDoc::OnBPNet()
{
	// TODO: �ڴ���������������
	CMnistPredictDlg m_mnist_predict_Dlg;
	m_mnist_predict_Dlg.DoModal();
}
void CusefulDoc::OnLoadTriangle()
{
	// TODO: �ڴ���������������
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal()==IDOK)
	{
		CString m_str=fileDlg.GetPathName();
		m_tinNet.clear();m_triVex.clear();
		//char* pathTri="D:\\testdata\\gdal_triagle.txt";
		load_triangle_file(m_tinNet,m_triVex,m_str);
		m_triShow=TRUE;m_gridShow=FALSE;
		UpdateAllViews(0,0,0);
	}
}
void CusefulDoc::OnLoadGrid()
{
	// TODO: �ڴ���������������
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal()==IDOK)
	{
		CString m_str=fileDlg.GetPathName();
		m_grid.clear();
		load_grid_file(m_grid,m_str);
		m_gridShow=TRUE;m_triShow=FALSE;
		UpdateAllViews(0,0,0);
	}
}
void CusefulDoc::On3DView()
{
	// TODO: �ڴ���������������
	CDialog3D m_3DView;
	m_3DView.DoModal();
}
void CusefulDoc::OnClear()
{
	// TODO: �ڴ���������������
	m_grid.clear();
	m_tinNet.clear();
	m_triVex.clear();
	m_shpPath.clear();
	m_dbfPath.clear();
	m_shp_Show=m_gridShow=m_triShow=FALSE;
	UpdateAllViews(0,0,0);
}


void CusefulDoc::OnShpClear()
{
	// TODO: �ڴ���������������
	m_shpPath.clear();
	m_dbfPath.clear();
	if ( m_pDataSource != 0 )
	{
		delete m_pDataSource ;
		m_pDataSource = 0 ;
	}
	m_shp_Show=FALSE;
	UpdateAllViews(0,0,0);
}
