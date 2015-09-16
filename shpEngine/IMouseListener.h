
#ifndef IMouseListener_h
#define IMouseListener_h 1


//��������
enum 
{
	EMAP_TOOL_NULL	= 0,					// ȱʡ״̬�µĹ���״̬

	EMAP_TOOL_MAPVIEW_CONTROLLER = 10,		// ��ͼ�Ŀ��ƹ��ߡ�  ���ӹ��߰�����
									
		EMAP_TOOL_ZOOMIN = 11,				// ��С
		EMAP_TOOL_ZOOMOUT = 12,				// �Ŵ�
		EMAP_TOOL_PAN = 13					// ץȡ������Ļ
};

class CMouseEvent;

class IMouseListener
{

  public:

      //	�����������¡�
      virtual void OnLButtonDown (CMouseEvent* pMouseEvent) = 0;

      //	��������̧��
      virtual void OnLButtonUp (CMouseEvent* pMouseEvent) = 0;

      //	��������˫����
      virtual void OnLButtonDBLClick (CMouseEvent* pMouseEvent) = 0;

      //	����Ҽ������¡�
      virtual void OnRButtonDown (CMouseEvent* pMouseEvent) = 0;

      //	����Ҽ���̧��
      virtual void OnRButtonUp (CMouseEvent* pMouseEvent) = 0;

      //	����ƶ�
      virtual void OnMouseMove (CMouseEvent* pMouseEvent) = 0;

      //	����϶�
      virtual void OnMouseDrag (CMouseEvent* pMouseEvent) = 0;

      //	ȡ��������
      virtual void OnCancel () = 0;

};

#endif
