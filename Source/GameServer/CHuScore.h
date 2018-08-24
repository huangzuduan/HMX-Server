#ifndef _CHuScore_H_
#define _CHuScore_H_

#include "Global.hpp"

#pragma pack(push,1)
struct MyStruct
{
	int32_t id;
	int32_t val;
};
#pragma pack(pop)

class CHuScore : public Single<CHuScore>
{
public:
	CHuScore();
	~CHuScore();
	void Load(const std::string& filename);
	int16_t GetPaiXingScore(::msg_maj::hu_type hutype) const;
private:

	std::map<int32_t, int32_t> m_mapTypeScore;
};

#endif


