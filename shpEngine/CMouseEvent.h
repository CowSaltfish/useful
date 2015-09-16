
#ifndef CMouseEvent_h
#define CMouseEvent_h 

//	CMouseEvent�ࣺ����¼��ࡣ
class CMouseEvent
{
  public:
      //	���캯����
      //	�ڹ���ö���ʱ����ʼ������Ա������
      CMouseEvent (void* pSource, CPoint point, int mouseFlag, int theTool = -1);
      ~CMouseEvent();


      //	��ȡ��ǰ������ڵ�����ꡣ������Ϊ�豸���ꡣ
      CPoint GetPoint ();

      //	��ȡ��ǰ�����Ƽ���״̬��
      int GetMouseFlag ();

      //	��ȡ��ǰ�������ߵ��ӹ������͡�
      int GetTool ();

	  void* GetSource ();

  private:
      //	��ǰ������ڵ�����ꡣ������Ϊ�豸���ꡣ
      CPoint m_Point;
      //	������ǰ�Ƿ��п��Ƽ������¡����EGIS_MouseFlag��˵����
      int m_MouseFlag;
      //	��ǰ�������ߵ��ӹ������͡�
      int m_tool;
	  void* m_pSource;
};

#endif
