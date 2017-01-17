#ifndef _QUESTION_ANSWER_H_
#define _QUESTION_ANSWER_H_

#include "BaseDefine.h"
#include "Single.h"

class SceneUser;

class QuestionAnswer
{
public:
	QuestionAnswer(SceneUser* user);
	~QuestionAnswer();

	void doSendAskCateList();
	void doSendQAList(int32 cateid);
	void doRecvQA(int32 cateid,const char* ask,const char* answer);

private:

	SceneUser* pOwner;
};


class QuestionAnswerCfgMgr : public Single<QuestionAnswerCfgMgr>
{

};


#endif

