#ifndef __ATTRIBUTE_OFFSET_H_
#define __ATTRIBUTE_OFFSET_H_

#include "ServerDefine.h"

/*-------------------------------------------------------------------
 * @Brief : 属性管理器 
 * 
 * @Author:hzd 2015:11:27
 *------------------------------------------------------------------*/

template<typename TAttributeType,int32 TAttrMax>
class AttributeOffsetC
{
public:
	AttributeOffsetC(void){};
	~AttributeOffsetC(void){};

	/*-------------------------------------------------------------------
	 * @Brief : 属性修改 
	 * 
	 * @Author:hzd 2015:11:27
	 *------------------------------------------------------------------*/
	virtual bool SetAttribute(TAttributeType eAttributeType, const ValueType& vNewValue)
	{
		// 检测是否有偏移值   
		if (m_sAttributeOffset[eAttributeType].nOffset && m_sAttributeOffset[eAttributeType].bCanSet)
		{
			SetAttribute(eAttributeType, vNewValue, false);
			return true;
		}
		else
		{
			return false;
		}
	}

	/*--------------------------------------------
	 *  @brief  : 属性修改 
	 *  @input	: bEnforce 强制修改 
	 *  @return :	
	 *-------------------------------------------*/ 
	bool SetAttribute(TAttributeType eAttributeType, const ValueType& vNewValue, bool bEnforce)
	{
		// 检测是否有偏移值  
		if (m_sAttributeOffset[eAttributeType].nOffset && (m_sAttributeOffset[eAttributeType].bCanSet || bEnforce))
		{
			// 比较新旧值 
			if (memcmp(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize))
			{
				// 保存旧值 
				ValueType vOldValue;
				memcpy(&vOldValue, m_sAttributeOffset[eAttributeType].nOffset, m_sAttributeOffset[eAttributeType].nSize);

				// 设置新值 
				memcpy(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize);

				// 回调 
				if (m_sAttributeOffset[eAttributeType].hHandler)
				{
					m_sAttributeOffset[eAttributeType].hHandler(vOldValue, vNewValue);
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}


	bool GetAttribute(TAttributeType i_eAttributeType, ValueType& o_vValue)
	{
		// 检测是否有偏移值 
		if (m_sAttributeOffset[i_eAttributeType].nOffset)
		{
			memcpy(&o_vValue, m_sAttributeOffset[i_eAttributeType].nOffset, m_sAttributeOffset[i_eAttributeType].nSize);

			return true;
		}
		else
		{
			return false;
		}
	}

	int32 GetAttributeInt32(TAttributeType i_eAttributeType)
	{
		ValueType o_vValue;
		GetAttribute(i_eAttributeType,o_vValue);
		return o_vValue.nInt32;
	}

	int64 GetAttributeInt64(TAttributeType i_eAttributeType)
	{
		ValueType o_vValue;
		GetAttribute(i_eAttributeType,o_vValue);
		return o_vValue.nInt64;
	}

	virtual void InitAttribute() = 0;

protected:

	AttributeOffset	m_sAttributeOffset[TAttrMax];		// 

};

#endif


