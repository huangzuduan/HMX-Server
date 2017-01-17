/**
 * \brief 地图物件屏索引定义
 */

#include <ScenesServer.h>

/**
 * \brief 设置场景宽高
 * \param scenewh 场景的宽高
 * \param screenMax 最大屏编号
 */
void zSceneEntryIndex::setSceneWH(const zPos sceneWH,const DWORD screenx,const DWORD screeny,const DWORD screenMax)
{
  this->sceneWH=sceneWH;
  this->screenx=screenx;
  this->screeny=screeny;
  for(int i = 0; i < zSceneEntry::SceneEntry_MAX; i++)
  {
    for(DWORD j=0; j < screenMax; j ++)
    {
      index[i][j];
    }
  }

  //预先建立地图九屏索引
  const int adjust[9][2] = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,0} };
  for(DWORD j=0; j < screenMax ; j ++)
  {
    int nScreenX = j % screenx;
    int nScreenY = j / screenx;
    //Zebra::logger->debug("%u,%u,%u",screenMax,nScreenX,nScreenY);
    //计算周围九屏
    {
      zPosIVector pv;
      for(int i = 0; i < 9; i++) {
        int x = nScreenX + adjust[i][0];
        int y = nScreenY + adjust[i][1];
        if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny) {
          pv.push_back(y * screenx + x);
        }
      }
      ninescreen.insert(NineScreen_map_value_type(j,pv));
    }
    //计算正向变化五屏或者三屏
    for(int dir = 0; dir < 8; dir++)
    {
      int start,end;
      zPosIVector pv;

      if (1 == dir % 2) {
        //斜方向
        start = 6;
        end = 10;
      }
      else {
        //正方向
        start = 7;
        end = 9;
      }
      for(int i = start; i <= end; i++) {
        int x = nScreenX + adjust[(i + dir) % 8][0];
        int y = nScreenY + adjust[(i + dir) % 8][1];
        if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny) {
          pv.push_back(y * screenx + x);
        }
      }
      direct_screen[dir].insert(NineScreen_map_value_type(j,pv));
    }
    //计算反向变化五屏或者三屏
    for(int dir = 0; dir < 8; dir++)
    {
      int start,end;
      zPosIVector pv;

      if (1 == dir % 2) {
        //斜方向
        start = 2;
        end = 6;
      }
      else {
        //正方向
        start = 3;
        end = 5;
      }
      for(int i = start; i <= end; i++) {
        int x = nScreenX + adjust[(i + dir) % 8][0];
        int y = nScreenY + adjust[(i + dir) % 8][1];
        if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny) {
          pv.push_back(y * screenx + x);
        }
      }
      reversedirect_screen[dir].insert(NineScreen_map_value_type(j,pv));
    }
  }
}

/**
 * \brief 刷新场景物件
 * 如果没有添加物件,如果有刷新
 * 必须保证新坐标的合法性,这个函数里面不会验证坐标的合法性
 * \param e 要刷新的场景物件
 * \param newPos 物件的新坐标
 * \return 刷新是否成功
 */
bool zSceneEntryIndex::refresh(zSceneEntry *e,const zPos & newPos)
{
  if (e==NULL) return false;
  //zSceneEntry::SceneEntryType type = e->getType();
  //if (e->inserted)
  //{
  //  //已经加入地图,只是在屏之间来回切换
  //  bool ret=false;
  //  zPosI orgscreen=e->getPosI();

  //  SceneEntry_SET &pimi = index[type][orgscreen];
  //  SceneEntry_SET::iterator it = pimi.find(e);
  //  if (it != pimi.end() && e->setPos(sceneWH,newPos))
  //  {
  //    ret=true;
  //    if (orgscreen!=e->getPosI())
  //    {
  //      //Zebra::logger->debug("%s 切屏(%ld->%ld)",e->name,orgscreen,e->getPosI());
  //      pimi.erase(it);
  //      index[type][e->getPosI()].insert(e);
  //      if (type == zSceneEntry::SceneEntry_Player)
  //      {
  //        freshEffectPosi(orgscreen,e->getPosI());
  //        freshGateScreenIndex((SceneUser*)e,e->getPosI());
  //      }
  //    }
  //  }

  //  return ret;
  //}
  //else
  //{
  //  //新加入地图
  //  if (e->setPos(sceneWH,newPos))
  //  {
  //    index[type][e->getPosI()].insert(e);
  //    //在全局索引中添加
  //    all[type].insert(e);
  //    //在npc索引中添加
  //    if (zSceneEntry::SceneEntry_NPC == type )
  //    {
  //      SceneNpc *npc = (SceneNpc *)e;
  //      special_index[npc->id].insert(npc);
  //      //在功能npc索引中添加
  //      if (npc->isFunctionNpc())
  //      {
  //        functionNpc.insert(npc);
  //      }
  //    }
  //    if (type == zSceneEntry::SceneEntry_Player)
  //    {
  //      freshEffectPosi((zPosI)-1,e->getPosI());
  //      freshGateScreenIndex((SceneUser*)e,e->getPosI());
  //    }

  //    e->inserted=true;
  //    //Zebra::logger->debug("%s(%x) really inserted into scene entry index",e->name,e);
  //    //Zebra::logger->debug("%s 加入地图(%d,%d,%d)",e->name,e->getPosI(),e->getPos().x,e->getPos().y);
  //  }
  //  else
  //    Zebra::logger->debug("向屏索引插入 %s 失败 (%u,%u)",e->name,newPos.x,newPos.y);

  //  return e->inserted;
  //}
  return false;
}

/**
 * \brief 移出场景物件
 * \param e 要移出的场景物件
 * \return  true移出成功,false 失败
 */
bool zSceneEntryIndex::removeSceneEntry(zSceneEntry *e)
{
  //if (e==NULL || !e->inserted) return false;

  //zSceneEntry::SceneEntryType type = e->getType();
  //SceneEntry_SET &pimi = index[type][e->getPosI()];
  //SceneEntry_SET::iterator it = pimi.find(e);
  //if (it != pimi.end())
  //{
  //  //在屏索引中删除
  //  pimi.erase(it);
  //  //在全局索引中删除
  //  all[type].erase(e);
  //  //在npc索引中删除
  //  if (zSceneEntry::SceneEntry_NPC == type )
  //  {
  //    SceneNpc *npc = (SceneNpc *)e;
  //    special_index[npc->id].erase(npc);
  //    //在功能npc索引中删除
  //    if (npc->isFunctionNpc())
  //    {
  //      functionNpc.erase(npc);
  //    }
  //  }
  //  if (type == zSceneEntry::SceneEntry_Player)
  //  {
  //    freshEffectPosi(e->getPosI(),(zPosI)-1);
  //    freshGateScreenIndex((SceneUser*)e,(DWORD)-1); //-1表示从当前屏索引中删除
  //  }
  //  e->inserted=false;
  //  //Zebra::logger->debug("%s(%x) really removed from scene entry index",e->name,e);
  //  return true;
  //}

  return false;
}

/**
 * \brief 遍历一屏的物件,并对其操作
 * 遍历所有,包括所有的物件类型
 * \param screen 某一屏的屏编号
 * \param callback 要对物件进行操作的回调类
 */
void zSceneEntryIndex::execAllOfScreen(const zPosI screen,zSceneEntryCallBack &callback)
{
  for(int i = 0; i < zSceneEntry::SceneEntry_MAX; i++)
  {
    SceneEntry_SET &pimi = index[i][screen];
    for(SceneEntry_SET::iterator it=pimi.begin();it!=pimi.end();)
    {
      //预先保存迭代器,防止回调中使迭代器失效
      SceneEntry_SET::iterator tmp = it;
      it++;
      zSceneEntry *eee = *tmp;
      if (!callback.exec(eee)) return;
    }
  }
}

/**
 * \brief 遍历一屏的物件,并对其操作
 * 遍历特定类型的所有物件
 * \param type 物件类型
 * \param screen 某一屏的屏编号
 * \param callback 要对物件进行操作的回调类
 */
void zSceneEntryIndex::execAllOfScreen(const zSceneEntry::SceneEntryType type,const zPosI screen,zSceneEntryCallBack &callback)
{
  SceneEntry_SET &pimi = index[type][screen];
  for(SceneEntry_SET::iterator it=pimi.begin();it!=pimi.end();)
  {
    //预先保存迭代器,防止回调中使迭代器失效
    SceneEntry_SET::iterator tmp = it;
    it++;
    zSceneEntry *eee = *tmp;
    if (!callback.exec(eee)) return;
  }
}

/**
 * \brief 遍历一屏的物件,并对其操作
 * 遍历所有,包括所有的物件类型
 * \param callback 要对物件进行操作的回调类
 */
void zSceneEntryIndex::execAllOfScene(zSceneEntryCallBack &callback)
{
  for(int i = 0; i < zSceneEntry::SceneEntry_MAX; i++)
  {
    for(SceneEntry_SET::iterator it = all[i].begin(); it != all[i].end();)
    {
      //预先保存迭代器,防止回调中使迭代器失效
      SceneEntry_SET::iterator tmp = it;
      it++;
      zSceneEntry *eee = *tmp;
      if (!callback.exec(eee)) return;
    }
  }
}

/**
 * \brief 遍历一屏的物件,并对其操作
 * 遍历特定类型的所有物件
 * \param type 物件类型
 * \param callback 要对物件进行操作的回调类
 */
void zSceneEntryIndex::execAllOfScene(const zSceneEntry::SceneEntryType type,zSceneEntryCallBack &callback)
{
  for(SceneEntry_SET::iterator it = all[type].begin(); it != all[type].end();)
  {
    //预先保存迭代器,防止回调中使迭代器失效
    SceneEntry_SET::iterator tmp = it;
    it++;
    zSceneEntry *eee = *tmp;
    if (!callback.exec(eee)) return;
  }
}

/**
 * \brief 遍历地图上所有特定类型的npc,对其调用回调函数
 * 注：此回调只提供遍历执行,不提供删除功能
 * \param id npc类型
 * \param callback 回调函数
 */
void zSceneEntryIndex::execAllOfScene_npc(const DWORD id,zSceneEntryCallBack &callback)
{
 /* SpecialNpc_Index::iterator my_it = special_index.find(id);
  if (special_index.end() != my_it)
  {
    for(Npc_Index::iterator it = my_it->second.begin(); it != my_it->second.end(); ++it)
    {
      if (!callback.exec(*it)) return;
    }
  }*/
}

/**
 * \brief 遍历地图上所有功能npc,对其调用回调函数
 * 注：此回调只提供遍历执行,不提供删除功能
 * \param callback 回调函数
 */
void zSceneEntryIndex::execAllOfScene_functionNpc(zSceneEntryCallBack &callback)
{
  /*for(Npc_Index::iterator it = functionNpc.begin(); it != functionNpc.end(); ++it)
  {
    if (!callback.exec(*it)) return;
  }*/
}

/**
 * \brief 根据坐标,获取站在这个坐标点上面的地图物件
 * \param type 物件类型
 * \param pos 坐标点
 * \param bState 是否判断物件状态
 * \param byState 物件状态
 * \return 地图物件
 */
zSceneEntry *zSceneEntryIndex::getSceneEntryByPos(zSceneEntry::SceneEntryType type,const zPos &pos,const bool bState,const zSceneEntry::SceneEntryState byState)
{
  class GetSceneEntryByPos : public zSceneEntryCallBack
  {
    public:
      const zPos &pos;
      zSceneEntry *sceneEntry;
      bool _bState;
      zSceneEntry::SceneEntryState _byState;

      GetSceneEntryByPos(const zPos &pos,const bool bState,const zSceneEntry::SceneEntryState byState)
        : pos(pos),sceneEntry(NULL),_bState(bState),_byState(byState) {}
      bool exec(zSceneEntry *e)
      {
        if (e->getPos() == pos)
        {
          // 由于死亡状态和隐藏状态的Entry都在屏索引中,所以加上这句变成带状态的检索
          //if (_bState && e->getState() != _byState)
          //  return true;
          ////使根据位置取图腾陷阱类的npc无法取出
          //if (e->getType() == zSceneEntry::SceneEntry_NPC
          //    && ((SceneNpc *)e)->getPetType() == Cmd::PET_TYPE_TOTEM)
          //{
          //  return true;
          //}
          //sceneEntry = e;
          return false;
        }
        else
          return true;
      }
  } ret(pos,bState,byState);
  zPosI screen;
  zSceneEntry::zPos2zPosI(sceneWH,pos,screen);
  execAllOfScreen(type,screen,ret);
  return ret.sceneEntry;
}


/**
 * \brief 维护影响npc的屏
 * \param oldscreen 用户切屏前编号(-1表示只插入)
 * \param newscreen 用户切屏后编号(-1表示只删除)
 */
void zSceneEntryIndex::freshEffectPosi(const zPosI oldposi,const zPosI newposi)
{
  if (oldposi != (zPosI)-1)
  {
    const zPosIVector &pv = getNineScreen(oldposi);
    for(zPosIVector::const_iterator it = pv.begin(); it != pv.end(); it++)
    {
      PosiEffectMap_iter iter = posiEffect[(*it)%MAX_NPC_GROUP].find(*it);
      if (iter != posiEffect[(*it)%MAX_NPC_GROUP].end() && iter->second > 0)
      {
        iter->second--;
        if (iter->second == 0)
        {
          posiEffect[(*it)%MAX_NPC_GROUP].erase(iter);
          //Zebra::logger->debug("删除有效屏索引%d",iter->first);
        }
      }
    }
  }
  if (newposi != (zPosI)-1)
  {
    const zPosIVector &pv = getNineScreen(newposi);
    for(zPosIVector::const_iterator it = pv.begin(); it != pv.end(); it++)
    {
      posiEffect[(*it)%MAX_NPC_GROUP][*it]++;
      //Zebra::logger->debug("添加有效屏索引%d,有效次数%d",*it,posiEffect[(*it)%MAX_NPC_GROUP][*it]);
    }
  }
}

void zSceneEntryIndex::execAllOfEffectNpcScreen(const DWORD group,zSceneEntryCallBack &callback)
{
  PosiEffectMap_iter iter = posiEffect[group%MAX_NPC_GROUP].begin();
  for( ;iter != posiEffect[group%MAX_NPC_GROUP].end() ; iter++)
  {
    /*
    //预先保存迭代器,防止回调中使迭代器失效
    PosiEffectMap_iter iter_tmp = iter; 
    iter++;
    SceneEntry_SET &pimi = index[zSceneEntry::SceneEntry_NPC][iter_tmp->first];
    // */
    // 这里无论如何移动,只要不超过9屏,就不会引起本屏的无效,但是可能会引起iter++的无效,
    // 所以不能先++再处理
    SceneEntry_SET &pimi = index[zSceneEntry::SceneEntry_NPC][iter->first];
    for(SceneEntry_SET::iterator it=pimi.begin();it!=pimi.end();)
    {
      //预先保存迭代器,防止回调中使迭代器失效
      SceneEntry_SET::iterator tmp = it;
      it++;
      zSceneEntry *eee = *tmp;
      if (!callback.exec(eee)) return;
    }
  }
}

/**
 * \brief 得到某一位置一定范围内的屏列表
 * \param pos 指定坐标
 * \param range 指定范围
 * \return 屏列表
 */
const zPosIVector &zSceneEntryIndex::getScreenByRange(const zPos &pos,const int range)
{
  static zPosIVector pv;
  pv.clear();
  int scnX = pos.x / SCREEN_WIDTH;//屏编号
  int scnY = pos.y / SCREEN_HEIGHT;
  int offX = pos.x % SCREEN_WIDTH;//在一屏中的位置
  int offY = pos.y % SCREEN_HEIGHT;

  int x=0,y=0;

  //本屏
  x = scnX;
  y = scnY;
  if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
    pv.push_back(y * screenx + x);

  if (offX<range)
  {
    //左
    x = scnX - 1;
    y = scnY;
    if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
      pv.push_back(y * screenx + x);

    if (offY<range)
    {
      //上
      x = scnX;
      y = scnY - 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);

      //左上
      x = scnX - 1;
      y = scnY - 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);
    }

    if (offY+range>SCREEN_HEIGHT)
    {
      //下
      x = scnX;
      y = scnY + 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);

      //左下
      x = scnX - 1;
      y = scnY + 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);
    }
  }

  if (offX+range>SCREEN_WIDTH)
  {
    //右
    x = scnX + 1;
    y = scnY;
    if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
      pv.push_back(y * screenx + x);

    if (offY<range)
    {
      //上
      x = scnX;
      y = scnY - 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);

      //右上
      x = scnX + 1;
      y = scnY - 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);
    }

    if (offY+range>SCREEN_HEIGHT)
    {
      //下
      x = scnX;
      y = scnY + 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);

      //右下
      x = scnX + 1;
      y = scnY + 1;
      if (x >= 0 && y >= 0 && x < (int)screenx && y < (int)screeny)
        pv.push_back(y * screenx + x);
    }
  }
  return pv;
}

