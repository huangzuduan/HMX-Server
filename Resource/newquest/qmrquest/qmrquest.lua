--算法请使用lua语法自己开发.
----------------------------------------------------------

--level  角色等级
--lastonlinetime  昨天在线时间(单位：秒)
function cangetsalary(level,lastonlinetime)
	if level >= 100 and lastonlinetime >=60*60  then
		return 30000;
	end
	if level >= 80 and lastonlinetime >=60*60  then
		return 20000;
	end
	if level >= 60 and lastonlinetime >=60*60  then
		return 10000;
	end
end

--level  角色等级
--needexp  升下一级需要的经验
--exploit  需要兑换功勋值
function exploit2exp(level,needexp,exploit)
	return  (level * 5) * exploit;
end

--level  角色等级
--needexp  升下一级需要的经验
--grace   需要兑换的文采值
function grace2exp(level,needexp,grace)
	return  (level * 5) * grace;
end