#include "OfflineUser.h"
#include "GameService.h"


OfflineUser::OfflineUser(const ::msg_maj::RoleOff& proto)
{
	dataProto.CopyFrom(proto);
}

OfflineUser::~OfflineUser()
{

}
