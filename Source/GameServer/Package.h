#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "srvEngine.h"
#include "ScenesServer.h"

//SKY 包袱的宽和高
#define PACK_WIDTH	7
#define PACK_HEIGHT	35

//SKY  仓库的宽和高
#define SAVEBOX_WIDTH 7
#define SAVEBOX_HEIGHT 50

#define DECLARE(prop,type) type get_##prop() const {return prop;}
#define RESET(prop) prop = 0;
class Equips
{
public:
	Equips()
	{
		reset();
	}

	void reset()
	{
		RESET(maxhp)          // 最大生命值
			RESET(maxmp)          // 最大法术值
			RESET(maxsp)          // 最大体力值

			RESET(pdamage)          // 最小攻击力
			RESET(maxpdamage)        // 最大攻击力
			RESET(mdamage)          // 最小法术攻击力
			RESET(maxmdamage)        // 最大法术攻击力
			RESET(appendminpet)           // 宠物增强最小值
			RESET(appendmaxpet)        // 宠物增强最大值

			RESET(pdefence)        // 物防
			RESET(mdefence)        // 魔防
			RESET(damagebonus)      // 伤害加成
			RESET(damage)        // 增加伤害值x％

			RESET(akspeed)        // 攻击速度
			RESET(mvspeed)        // 移动速度
			RESET(atrating)        // 命中率
			RESET(akdodge)        // 躲避率

			RESET(str)            // 力量
			RESET(inte)            // 智力
			RESET(dex)            // 敏捷
			RESET(spi)            // 精神
			RESET(con)            // 体质

			RESET(hpr)          // 生命值恢复
			RESET(mpr)            // 法术值恢复
			RESET(spr)            // 体力值恢复

			RESET(holy)            //神圣一击
			RESET(bang)            //重击率
			RESET(pdam)           // 增加物理攻击力
			RESET(pdef)            // 增加物理防御力
			RESET(mdam)            // 增加魔法攻击力
			RESET(mdef)            // 增加魔法防御力

			RESET(poisondef)         //抗毒增加
			RESET(lulldef)         //抗麻痹增加
			RESET(reeldef)         //抗眩晕增加
			RESET(evildef)         //抗噬魔增加
			RESET(bitedef)         //抗噬力增加
			RESET(chaosdef)         //抗混乱增加
			RESET(colddef)         //抗冰冻增加
			RESET(petrifydef)       //抗石化增加
			RESET(blinddef)         //抗失明增加
			RESET(stabledef)         //抗定身增加
			RESET(slowdef)         //抗减速增加
			RESET(luredef)         //抗诱惑增加

			RESET(poison)         //中毒增加
			RESET(lull)           //麻痹增加
			RESET(reel)           //眩晕增加
			RESET(evil)           //噬魔增加
			RESET(bite)          //噬力增加
			RESET(chaos)           //混乱增加
			RESET(cold)           //冰冻增加
			RESET(petrify)         //石化增加
			RESET(blind)           //失明增加
			RESET(stable)         //定身增加
			RESET(slow)           //减速增加
			RESET(lure)           //诱惑增加
			RESET(hpleech.odds)
			RESET(hpleech.effect)
			RESET(mpleech.odds)       //x%吸收生命值y
			RESET(mpleech.effect)     //x%吸收法术值y

			RESET(hptomp)          //转换生命值为法术值x％
			RESET(dhpp)           //物理伤害减少x%  
			RESET(dmpp)          //法术伤害值减少x%    

			RESET(incgold)        //增加金钱掉落x%
			RESET(doublexp)        //x%双倍经验    
			RESET(mf)             //增加掉宝率x%

								  //五行套装相关属性
			RESET(dpdam)      //物理伤害减少%x
			RESET(dmdam)      //法术伤害减少%x
			RESET(bdam)        //增加伤害x%
			RESET(rdam)        //伤害反射%x
			RESET(ignoredef)    //%x忽视目标防御

								//    RESET(aftype)
			aftype = FIVE_NONE;
		RESET(afpoint)
			//    RESET(dftype)
			dftype = FIVE_NONE;
		RESET(dfpoint)
			RESET(maxhprate)
			RESET(maxmprate)

			RESET(Freedom.str_Attribute)
			RESET(Freedom.inte_Attribute)
			RESET(Freedom.dex_Attribute)
			RESET(Freedom.spi_Attribute)
			RESET(Freedom.con_Attribute)

			skill.clear();
		skills.clear();

		gempop.clear();
	}

	DECLARE(maxhp, WORD)        // 最大生命值
		DECLARE(maxmp, WORD)        // 最大法术值
		DECLARE(maxsp, WORD)        // 最大体力值

		DECLARE(pdamage, WORD)      // 最小攻击力
		DECLARE(maxpdamage, WORD)    // 最大攻击力
		DECLARE(mdamage, WORD)      // 最小法术攻击力
		DECLARE(maxmdamage, WORD)    // 最大法术攻击力
		DECLARE(appendminpet, WORD)  // 最小宠物增强
		DECLARE(appendmaxpet, WORD)  // 最大宠物增强

		DECLARE(pdefence, WORD)      // 物防
		DECLARE(mdefence, WORD)      // 魔防
		DECLARE(damagebonus, BYTE)    // 伤害加成
		DECLARE(damage, BYTE)        // 增加伤害值x％

		DECLARE(akspeed, WORD)      // 攻击速度
		DECLARE(mvspeed, WORD)      // 移动速度
		DECLARE(atrating, WORD)      // 命中率
		DECLARE(akdodge, WORD)      // 躲避率

		DECLARE(str, WORD)          // 力量
		DECLARE(inte, WORD)         // 智力
		DECLARE(dex, WORD)         // 敏捷
		DECLARE(spi, WORD)          // 精神
		DECLARE(con, WORD)          // 体质

		DECLARE(hpr, WORD)          // 生命值恢复
		DECLARE(mpr, WORD)          // 法术值恢复
		DECLARE(spr, WORD)          // 体力值恢复

		DECLARE(holy, WORD)        //神圣一击
		DECLARE(bang, WORD)        //重击率
		DECLARE(pdam, WORD)          // 增加物理攻击力
		DECLARE(pdef, WORD)          // 增加物理防御力
		DECLARE(mdam, WORD)          // 增加魔法攻击力
		DECLARE(mdef, WORD)          // 增加魔法防御力

		DECLARE(poisondef, WORD)       //抗毒增加
		DECLARE(lulldef, WORD)       //抗麻痹增加
		DECLARE(reeldef, WORD)       //抗眩晕增加
		DECLARE(evildef, WORD)       //抗噬魔增加
		DECLARE(bitedef, WORD)       //抗噬力增加
		DECLARE(chaosdef, WORD)       //抗混乱增加
		DECLARE(colddef, WORD)       //抗冰冻增加
		DECLARE(petrifydef, WORD)     //抗石化增加
		DECLARE(blinddef, WORD)       //抗失明增加
		DECLARE(stabledef, WORD)       //抗定身增加
		DECLARE(slowdef, WORD)       //抗减速增加
		DECLARE(luredef, WORD)       //抗诱惑增加

		DECLARE(poison, WORD)       //中毒增加
		DECLARE(lull, WORD)         //麻痹增加
		DECLARE(reel, WORD)         //眩晕增加
		DECLARE(evil, WORD)         //噬魔增加
		DECLARE(bite, WORD)         //噬力增加
		DECLARE(chaos, WORD)         //混乱增加
		DECLARE(cold, WORD)         //冰冻增加
		DECLARE(petrify, WORD)       //石化增加
		DECLARE(blind, WORD)         //失明增加
		DECLARE(stable, WORD)       //定身增加
		DECLARE(slow, WORD)         //减速增加
		DECLARE(lure, WORD)         //诱惑增加

		DECLARE(hptomp, BYTE)       //转换生命值为法术值x％
		DECLARE(dhpp, BYTE)         //物理伤害减少x%  
		DECLARE(dmpp, BYTE)         //法术伤害值减少x%    

		DECLARE(incgold, BYTE)       //增加金钱掉落x%
		DECLARE(doublexp, BYTE)       //x%双倍经验    
		DECLARE(mf, BYTE)         //增加掉宝率x%

								  //五行套装相关属性
		DECLARE(dpdam, BYTE)      //物理伤害减少%x
		DECLARE(dmdam, BYTE)      //法术伤害减少%x
		DECLARE(bdam, BYTE)        //增加伤害x%
		DECLARE(rdam, BYTE)        //伤害反射%x
		DECLARE(ignoredef, BYTE)    //%x忽视目标防御
		DECLARE(maxhprate, BYTE)    //按百分比增加最大hp
		DECLARE(maxmprate, BYTE)    //按百分比增加最大mp

									//sky 新增自由加点的属性 
		WORD get_Freedom_str()		const { return Freedom.str_Attribute; }
	WORD get_Freedom_inte()		const { return Freedom.inte_Attribute; }
	WORD get_Freedom_dex()		const { return Freedom.dex_Attribute; }
	WORD get_Freedom_spi()		const { return Freedom.spi_Attribute; }
	WORD get_Freedom_con()		const { return Freedom.con_Attribute; }

	BYTE get_hpleech_odds()    const { return hpleech.odds; }
	WORD get_hpleech_effect()  const { return hpleech.effect; }	 //x%吸收生命值y
	BYTE get_mpleech_odds()    const { return mpleech.odds; }
	WORD get_mpleech_effect()  const { return mpleech.effect; }     //x%吸收法术值y

																	/**
																	* \brief sky 获取宝石属性
																	* \return 攻击五行类型
																	*/
	WORD get_gem_str() const   //获取宝石的力量
	{
		WORD str;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				str += it->gem_str;
		}

		return str;
	}

	WORD get_gem_inte() const   //获取宝石的智力
	{
		WORD inte;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				inte += it->gem_inte;
		}

		return inte;
	}

	WORD get_gem_dex() const   //获取宝石的敏捷
	{
		WORD dex;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dex += it->gem_dex;
		}

		return dex;
	}

	WORD get_gem_spi() const   //获取宝石的精神
	{
		WORD spi;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				spi += it->gem_spi;
		}

		return spi;
	}

	WORD get_gem_con() const   //获取宝石的耐力
	{
		WORD con;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				con += it->gem_con;
		}

		return con;
	}

	WORD	gem_atk;	//物理攻击力
	WORD	gem_mkt;

	WORD get_gem_def() const   //获取宝石的物理防御
	{
		WORD def;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				def += it->gem_def;
		}

		return def;
	}

	WORD get_gem_mdef() const   //获取宝石的魔法防御
	{
		WORD mdef;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				mdef += it->gem_mdef;
		}

		return mdef;
	}

	WORD get_gem_dhpp() const   //获取宝石的物理免伤
	{
		WORD dhpp;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dhpp += it->gem_dhpp;
		}

		return dhpp;
	}

	WORD get_gem_dmpp() const   //获取宝石的魔法免伤
	{
		WORD dmpp;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				dmpp += it->gem_dmpp;
		}

		return dmpp;
	}

	WORD get_gem_atk() const   //获取宝石的物理攻击力
	{
		WORD atk;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				atk += it->gem_atk;
		}

		return atk;
	}

	WORD get_gem_mtk() const   //获取宝石的魔法攻击力
	{
		WORD mtk;
		const_iterator1 it;

		for (it = gempop.begin(); it != gempop.end(); it++)
		{
			if (it->GemID != INVALID_HOLE)
				mtk += it->gem_mkt;
		}

		return mtk;
	}

	/**
	* \brief 获取攻击五行
	* \return 攻击五行类型
	*/
	DWORD getAttFive() const { return aftype; }

	/**
	* \brief 获取攻击五行点数
	* \return 五行点数
	*/
	DWORD getAttFivePoint() const { return afpoint; }

	/**
	* \brief 获取防御五行
	* \return 防御五行类型
	*/
	DWORD getDefFive() const { return dftype; }

	/**
	* \brief 获取防御五行点数
	* \return 五行点数
	*/
	DWORD getDefFivePoint() const { return dfpoint; }

	/**
	* \brief 获取装备对单个技能的加成
	*
	* \param id: 技能id
	* \return 加成等级
	*/
	DWORD getMaxSkill(WORD id) const
	{
		const_iterator it = skill.find(id);
		if (it != skill.end()) {
			return it->second;
		}

		return 0;
	}

	/**
	* \brief 获取装备对某系技能的加成
	*
	* \param id: 技能系别
	* \return 加成等级
	*/
	DWORD getMaxSkills(WORD id) const
	{
		const_iterator it = skills.find(id);
		if (it != skills.end()) {
			return it->second;
		}

		return 0;
	}

private:
	friend class EquipPack;
	DWORD maxhp;          // 最大生命值
	DWORD maxmp;          // 最大法术值
	DWORD maxsp;          // 最大体力值

	DWORD pdamage;        // 最小攻击力
	DWORD maxpdamage;      // 最大攻击力
	DWORD mdamage;        // 最小法术攻击力
	DWORD maxmdamage;      // 最大法术攻击力
	WORD appendminpet;         // 给宠召唤兽能力增强最小值
	WORD appendmaxpet;         // 给宠召唤兽能力增强最大值

	WORD pdefence;        // 物防
	WORD mdefence;        // 魔防
	BYTE damagebonus;      // 伤害加成
	BYTE damage;        // 增加伤害值x％

	WORD akspeed;        // 攻击速度
	WORD mvspeed;        // 移动速度
	WORD atrating;        // 命中率
	WORD akdodge;        // 躲避率

	WORD str;  // 力量
	WORD inte;  // 智力
	WORD dex;  // 敏捷
	WORD spi;  // 精神
	WORD con;  // 体质


			   //      WORD fivetype;  // 五行属性
			   //      WORD fivepoint; // 五行属性

	WORD hpr;  // 生命值恢复
	WORD mpr;  // 法术值恢复
	WORD spr;  // 体力值恢复

	WORD holy;  //神圣一击  
	WORD bang;  //重击率
	WORD pdam;  // 增加物理攻击力
	WORD pdef;  // 增加物理防御力
	WORD mdam;  // 增加魔法攻击力
	WORD mdef;  // 增加魔法防御力

	WORD poisondef; //抗毒增加
	WORD lulldef; //抗麻痹增加
	WORD reeldef; //抗眩晕增加
	WORD evildef; //抗噬魔增加
	WORD bitedef; //抗噬力增加
	WORD chaosdef; //抗混乱增加
	WORD colddef; //抗冰冻增加
	WORD petrifydef; //抗石化增加
	WORD blinddef; //抗失明增加
	WORD stabledef; //抗定身增加
	WORD slowdef; //抗减速增加
	WORD luredef; //抗诱惑增加

	WORD poison; //中毒增加
	WORD lull; //麻痹增加
	WORD reel; //眩晕增加
	WORD evil; //噬魔增加
	WORD bite; //噬力增加
	WORD chaos; //混乱增加
	WORD cold; //冰冻增加
	WORD petrify; //石化增加
	WORD blind; //失明增加
	WORD stable; //定身增加
	WORD slow; //减速增加
	WORD lure; //诱惑增加

	struct leech
	{
		BYTE odds;    //x
		WORD effect;  //y
	};
	leech hpleech; //x%吸收生命值y
	leech mpleech; //x%吸收法术值y

	BYTE hptomp; //转换生命值为法术值x％
	BYTE dhpp; //物理伤害减少x%  
	BYTE dmpp; //法术伤害值减少x%    

	BYTE incgold; //增加金钱掉落x%
	BYTE doublexp; //x%双倍经验    
	BYTE mf; //增加掉宝率x%

	union {
		BYTE _five_props[5];
		struct {
			//五行套装相关属性
			BYTE dpdam; //物理伤害减少%x
			BYTE dmdam; //法术伤害减少%x
			BYTE bdam; //增加伤害x%
			BYTE rdam; //伤害反射%x
			BYTE ignoredef; //%x忽视目标防御
		};
	};

	WORD aftype;
	WORD afpoint;
	WORD dftype;
	WORD dfpoint;

	typedef std::map<WORD, WORD> SKILL;
	typedef SKILL::const_iterator const_iterator;
	SKILL skill;  //单个技能加成
	SKILL skills; //全系技能加成 
	BYTE maxhprate;  //按百分比增加最大hp
	BYTE maxmprate;  //按百分比增加最大mp

	struct Freedom_Attribute {
		WORD str_Attribute;		// 力量已经加过的自由点
		WORD inte_Attribute;	// 智力已经加过的自由点
		WORD dex_Attribute;		// 敏捷已经加过的自由点
		WORD spi_Attribute;		// 精神已经加过的自由点
		WORD con_Attribute;		// 体质已经加过的自由点

	} Freedom;

	//sky 新增宝石属性结构
	typedef std::vector<GemPop> GEMPOP;
	typedef GEMPOP::const_iterator const_iterator1;
	GEMPOP gempop;
};


struct PackageCallback
{
	virtual bool exec(zObject * o) = 0;
	virtual ~PackageCallback() {};
};

class Package :private zNoncopyable
{
protected:
	zObject** container;

	virtual bool add(zObject *object, bool find);
	virtual bool remove(zObject *object);
	virtual bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
public:
	Package(WORD type, DWORD id, WORD w, WORD h);
	virtual ~Package();

	virtual bool getObjectByZone(zObject **ret, WORD x, WORD y);
	virtual bool getObjectByID(zObject **ret, DWORD id);
	virtual void execEvery(PackageCallback &callback);

	virtual WORD space() const;
	virtual WORD size() const;
	WORD type() const;
	DWORD id() const;

	void setSpace(WORD);
private:
	friend class Packages;

	virtual void removeAll();
	bool find_space(WORD &x, WORD &y) const;
	virtual int position(WORD x, WORD y) const;

	WORD _type;
	DWORD _id;
	WORD _width;
	WORD _height;

	WORD _space;
	WORD _size;

};

#if 0
class MultiPack :public Package
{
protected:
	WORD width;
	WORD height;
	std::vector<std::vector<zObject *> >grid;
	std::set<zObject *> allset;
public:
	MultiPack(WORD type, DWORD id, WORD width, WORD height);
	virtual ~MultiPack();
	virtual bool add(zObject *object, bool find);
	virtual void remove(zObject *object);
	virtual void removeAll();
	virtual bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
	virtual bool getObjectByZone(zObject **ret, WORD x, WORD y, WORD width, WORD height);
	virtual void execEvery(PackageCallback &callback);
	virtual bool findSpace(WORD owidth, WORD oheight, WORD &x, WORD &y);
	std::set<zObject *> &getAllset()
	{
		return allset;
	}

	WORD get_width() const
	{
		return width;
	}

	WORD get_height() const
	{
		return height;
	}

};
#endif

class ObjectPack : public Package
{
public:
	ObjectPack(zObject* ob, int type = Cmd::OBJECTCELLTYPE_PACKAGE, bool consume = true);
	~ObjectPack();

	bool empty() const
	{
		return space() == size();
	}

	zObject* object()
	{
		return _ob;
	}

	void consume_dur_by(SceneUser* user, const zRTime& current);
	bool can_input()
	{
		if (!_ob || _ob->data.dur == 0) {
			return false;
		}
		return true;
	}

private:
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);
	//bool add(zObject *object,bool find);

	zObject* _ob;
	bool _cosume_by_time;
	Timer _one_min;
};


class EquipPack : public Package
{
public:

	enum EQUIPNO {
		BODY,
		HEAD,
		HANDL,
		HANDR,
		BELT,
		NECKLACE,//5

		RINGL,
		RINGR,
		BANGL,
		BANGR,
		BOOTS,//10

		OTHERS,
		OTHERS1,
		OTHERS2,
		OTHERS3,
		OTHERS4, //15  
	};

	enum PACKNO {
		R_PACK,
		L_PACK,
		R_MAKE,
		L_MAKE,
	};
	EquipPack(SceneUser* user);
	~EquipPack();

	DWORD doubleexp_obj;
	DWORD doubleexp_obj_time;
	DWORD family_obj_times;
	DWORD family_obj_time;
	DWORD tong_obj_times;
	DWORD tong_obj_time;
	DWORD king_obj_times;
	DWORD king_obj_time;
	const Equips &getEquips() const;
	ObjectPack* pack(PACKNO no) const;
	zObject* equip(EQUIPNO no) const;

	bool getObjectByZone(zObject **ret, WORD x, WORD y);
	zObject *getObjectByEquipNo(EQUIPNO no);
	zObject *getObjectByEquipPos(DWORD no);

	bool costAttackDur(SceneUser *pThis);
	bool costDefenceDur(SceneUser *pThis);
	bool costAttackDurByPet(SceneUser *pThis);
	bool costDefenceDurByPet(SceneUser *pThis);
	void restituteDurability(SceneUser *pThis, const zRTime &ct);
	void updateDurability(SceneUser *pThis, DWORD value);
	DWORD fullAllEquiped(char *buf);

	bool needRecalc;
	int effectCount;

	bool skillReduceObject(SceneUser* pThis, DWORD kind, WORD num);
	bool skillCheckReduceObject(SceneUser* pThis, DWORD id, WORD num);
	bool canChangeColor();
	void calcAll();
	int reduceDur(SceneUser *pThis, DWORD which, DWORD type, DWORD num, bool needFresh = true, bool needCal = true);
	bool isTonic();

	void obtain_exp(SceneUser* user, DWORD exp, bool force = false);

	//装备包裹是否为空
	bool isEmpty();
private:
	bool add(zObject *object, bool find);
	bool remove(zObject *object);
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);

	//sky 检测物品的装备职业是否符合当前玩家的职业                                                                     */
	bool IsJobEquip(DWORD useJob, DWORD EquipType);

	virtual int position(WORD x, WORD y) const;

	bool reduceDur(SceneUser *pThis, DWORD which);
	inline void freshDurability(SceneUser *pThis, zObject *o);
	inline void freshUserData(SceneUser *pThis);

	bool process_extra_add(zObject* ob);
	bool process_extra_remove(zObject* ob);
	bool process_extra_get(zObject** ob, WORD x, WORD y);

	SceneUser* owner;
	ObjectPack** packs;
	Equips equips;
	const static int _poses[60];

};

#define MAX_TAB_NUM 5
#define MIN_TAB_NUM 2

class MainPack :public Package
{
public:
	enum {
		//sky 设置包袱的格子有效区域
		WIDTH = PACK_WIDTH,
		HEIGHT = PACK_HEIGHT,
	};

	MainPack();
	~MainPack();

	BYTE TabNum; //sky 玩家可以使用的包裹页数

	bool getObjectByZone(zObject **ret, WORD x, WORD y);
	zObject * getGold();
	DWORD getGoldNum();

	bool skillReduceObject(SceneUser* pThis, DWORD kind, DWORD num);

private:
	bool add(zObject *object, bool find);
	bool remove(zObject *object);
	bool checkAdd(SceneUser *pUser, zObject *object, WORD x, WORD y);

	zObject *gold;
};

class StorePack : public Package
{
public:
	enum {
		W = SAVEBOX_WIDTH,
		H = SAVEBOX_HEIGHT,
	};

	BYTE days;

	StorePack();
	~StorePack();

	void goldstore(SceneUser *pThis, bool notify = true);
	int load(BYTE* dest);
	int save(BYTE* dest);

	void notify(SceneUser* user);

private:
	bool checkAdd(SceneUser* pUser, zObject* object, WORD x, WORD y);

};

class PetPack : public Package
{
public:
	static const BYTE W = 8;
	static const BYTE H = 10;

	PetPack();
	~PetPack();

	WORD size() const;//返回最大可用数
	void setAvailable(WORD);//设置最大可用数

	bool isEmpty() const;

private:
	WORD available;//可用的总数

	bool checkAdd(SceneUser* pUser, zObject* object, WORD x, WORD y);
};

template<typename T>
class Type2Type
{
public:
	typedef T BASE;
};

class GlobalObjectIndex :private zEntryMgr< zEntryID >
{
private:
	static GlobalObjectIndex *onlyme;
	zMutex mlock;

	GlobalObjectIndex();
	~GlobalObjectIndex();
public:
	static GlobalObjectIndex *getInstance();
	static void delInstance();
	void removeObject(DWORD thisid);
	bool addObject(zObject * o);
	zObject *getObjectByThisid(DWORD thisid);
};

extern GlobalObjectIndex *const goi;

class UserObjectCompare
{
public:
	virtual bool isIt(zObject * object) = 0;
};

class UserObjectExec
{
public:
	virtual bool exec(zObject * object) = 0;
};

class UserObjectM :private zEntryMgr< zEntryID >
{
public:
	typedef std::vector<DWORD > ObjID_vec;
	typedef std::vector<zObject *> Obj_vec;

	UserObjectM();
	~UserObjectM();
	zObject * getObjectByThisID(DWORD thisid);
	zObject *getObjectByPos(const stObjectLocation &dst);
	void removeObjectByThisID(DWORD thisid);
	void removeObject(zObject * o);
	bool addObject(zObject * o);
	zObject *getObject(UserObjectCompare &comp);
	void execEvery(UserObjectExec &exec);

	DWORD exist(DWORD id, DWORD number, BYTE upgrade = 0, BYTE type = 0) const;
	int space(const SceneUser* user) const;

	zObject* getObjectByID(DWORD id, BYTE upgrade = 0, bool not_need_space = false) const;
	int reduceObjectNum(SceneUser* user, DWORD id, DWORD number, zObject*& update_ob, ObjID_vec& del_obs, BYTE upgrade = 0);
	int addObjectNum(SceneUser* user, DWORD id, DWORD number, zObject* & orig_ob, Obj_vec& new_obs, BYTE upgrade);
	int addGreenObjectNum(SceneUser* user, DWORD id, DWORD number, zObject* & orig_ob, Obj_vec& new_obs, BYTE upgrade);
};

class Packages
{
private:
	SceneUser *owner;

	Package** getPackage(int packs);

public:
	enum {
		MAIN_PACK = 1,
		LEFT_PACK = 2,
		RIGHT_PACK = 4,
		EQUIP_PACK = 8,
		STORE_PACK = 16,
		LM_PACK = 32,
		RM_PACK = 64,
		PET_PACK = 128,
	};

	UserObjectM uom;
	MainPack main;
	EquipPack equip;
	StorePack store;
	PetPack petPack;

	Packages(SceneUser* user);
	~Packages();
	void addMoney(DWORD num, const char *disc, const char *note = NULL, bool notify = true);
	void addGold(DWORD num, const char *disc, const char *note = NULL, bool notify = true, bool pack = false);
	void addTicket(DWORD num, const char *disc, const char *note = NULL, bool notify = true);
	bool checkMoney(DWORD need);
	bool checkTicket(DWORD need);
	bool checkGold(DWORD need);
	bool removeMoney(DWORD num, const char *disc);
	bool removeGold(DWORD num, const char *disc, bool need = true);
	bool removeTicket(DWORD num, const char *disc);

	bool moveObject(SceneUser *pUser, zObject *srcObj, stObjectLocation &dst);
	bool moveObjectToScene(zObject *o, const zPos &pos, DWORD overdue_msecs = 0, const unsigned long dwID = 0);
	bool removeObject(zObject *srcObj, bool notify = true, bool del = true);
	bool addObject(zObject *srcObj, bool needFind, int packs = 0);
	Package* getPackage(DWORD type, DWORD id);
	SceneUser *getOwner()
	{
		return owner;
	}

	template<typename T>
	void execEvery(Package* pack, T t)
	{
		typename T::BASE cb(this);
		pack->execEvery(cb);
	}

	template<typename T, typename P1>
	void execEvery(Package* pack, T t, P1 p1)
	{
		typename T::BASE cb(this, p1);
		pack->execEvery(cb);
	}

	zObject *getGold();
	DWORD getGoldNum();
};

#define AUTO_PACK Packages::MAIN_PACK |Packages::LEFT_PACK| Packages::RIGHT_PACK

struct Combination : public PackageCallback
{
public:
	Combination(SceneUser* user, zObject* get) : _user(user), _get(get), _num(0)
	{ }

	virtual bool exec(zObject* o);

	int num() const
	{
		return _num;
	}

private:
	SceneUser* _user;
	zObject* _get;
	int _num;
};

struct ClearPack : public PackageCallback
{
public:
	ClearPack(const Packages* ps) : _ps(ps)
	{ }

	virtual bool exec(zObject* p);
private:
	const Packages* _ps;
};

struct DropFromPack : public PackageCallback
{
public:
	struct Param
	{
		Package* pack;
		int drop_num;
		zPos pos;

		Param(Package* p, int d, const zPos& s) : pack(p), drop_num(d), pos(s)
		{ }
	};

	DropFromPack(const Packages* ps, const Param&  p);
	virtual bool exec(zObject* ob);
private:
	const Packages* _ps;
	Param _p;

	int _begin;
	int _pos;
};


#endif // !1def 



