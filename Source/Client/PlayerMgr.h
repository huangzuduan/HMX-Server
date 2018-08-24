#ifndef __CLIENT_PLAYER_MGR_H_
#define __CLIENT_PLAYER_MGR_H_

#include "SrvEngine.h"
#include "Player.h"
#include "Single.h"

class PlayerMgr : protected zEntryMgr< zEntryID<0> >, public Single<PlayerMgr>
{
protected:
	friend class Single<PlayerMgr>;
	PlayerMgr();
	~PlayerMgr();
public:

	Player* CreateObj(zSession* _session);
	void DestoryObj(Player* obj);

	Player* get(int64_t id);
	bool add(Player* obj);
	void remove(Player* obj);

	void Update(const zTaskTimer* timer);

	template <class YourSessionEntry>
	bool execPlayer(execEntry<YourSessionEntry> &exec)
	{
		return execEveryEntry<>(exec);;
	}

private:

	zObjPool<Player>		objpool;
	std::vector<Player*>  connectings;
};

#endif


