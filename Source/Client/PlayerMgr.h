#ifndef __CLIENT_PLAYER_MGR_H_
#define __CLIENT_PLAYER_MGR_H_

#include "Player.h"


class PlayerMgr : protected zEntryMgr<zEntryID>, public Single<PlayerMgr>
{
protected:
	friend class Single<PlayerMgr>;
	PlayerMgr();
	~PlayerMgr();
public:

	Player* CreateObj();
	void DestoryObj(Player* obj);

	Player* get(int64 id);
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


