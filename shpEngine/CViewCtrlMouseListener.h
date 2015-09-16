

#ifndef CViewCtrlMouseListener_h
#define CViewCtrlMouseListener_h 

#include "IMouseListener.h"
class CViewCtrlMouseListener : public IMouseListener 
{

  public:
      CViewCtrlMouseListener();
      ~CViewCtrlMouseListener();

      //�����������¡�
      void OnLButtonDown (CMouseEvent* pMouseEvent);

      //��������̧��
      void OnLButtonUp (CMouseEvent* pMouseEvent);

      //��������˫����
      void OnLButtonDBLClick (CMouseEvent* pMouseEvent);

      //����Ҽ������¡�
      void OnRButtonDown (CMouseEvent* pMouseEvent);

      //����Ҽ���̧��
      void OnRButtonUp (CMouseEvent* pMouseEvent);

      //����ƶ�
      void OnMouseMove (CMouseEvent* pMouseEvent);

      //����϶�
      void OnMouseDrag (CMouseEvent* pMouseEvent);

      //ȡ��������
      void OnCancel ();

  private:
	  CPoint m_LButtonPoint ;
	  CPoint m_lastPoint ;

};
#endif
