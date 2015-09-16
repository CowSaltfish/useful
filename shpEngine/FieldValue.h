
#ifndef FieldValue_h
#define FieldValue_h 

//	��˵������һ���ֶε�ֵ
class FieldValue 
{

  public:
      FieldValue();

      ~FieldValue();


      int GetInt ();
      void SetInt (int value);
      double GetDouble ();
      void SetDouble (double value);
      const char* GetString ();
      void SetString (const char* value);

  private:
      char* m_pValue;
};
#endif
