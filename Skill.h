#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

class Skill
{
    private:
        std::string Name, StatusEffect, Cure;
        int STR, Cost;
        static std::set<Skill*> SkillList; //set of objects of type Skill
    public:
        Skill(std::string name, int str, int cost, std::string effect, std::string ailment)
        {
            Name = name;
            STR = str;
            Cost = cost;
            StatusEffect = effect;
            Cure = ailment;
            SkillList.insert(this);
        }
        std::string getName(){return Name;}
        int getSTR(){return STR;}
        int getCost(){return Cost;}
        std::string getStatusEffect(){return StatusEffect;}
        std::string getCure(){return Cure;}
        static std::set<Skill*> getSkillList(){return SkillList;}
        /*static Skill CheckSkill(std::string SkillName)
        {
            for(auto skill : SkillList)
                {
                    if(SkillName == skill->getName())
                        return *skill;
                }
        }*/
};
std::set<Skill*> Skill::SkillList;
Skill Fire("Fire",50,10,"BURN","DRY");
Skill Water("Water",30,7,"WET","BURN");
Skill Wind("Wind",20,5,"DRY","WET");
Skill Bash("Bash",40,20,"STUN","NONE");
Skill Heal("Heal",-40,20,"HEAL","NONE");
#endif // SKILL_H_INCLUDED
