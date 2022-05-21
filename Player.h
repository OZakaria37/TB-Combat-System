#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class InvalidInputException : public std::logic_error //RETURNS EXCEPTION IN CASE OF INVALID INPUT
{
    public:
        InvalidInputException()

            : logic_error("ERROR : Entered Invalid Input\n")
            {}
};

class InsufficientAPException : public std::logic_error //RETURNS EXCEPTION IN CASE OF INVALID SKILL USAGE DUE TO AP LIMIT
{
    public:
        InsufficientAPException()

            : logic_error("ERROR : Insufficient AP To Use Skill\n")
            {}
};

class Player
{
    private:
        std::string Name, Style;
        int HP, MaxHP, STR, SPD, AP, MaxAP, TurnBar = 0, LVL = 1, XP = 0;
        std::vector<Skill> Skills;
        std::set<std::string> StatusEffects, ValidActions = {"Attack"}, ValidTargets;
        static int MaxLVL;
        static std::set<Player*> PlayerList; //set of objects of type Skill
    public:
        Player(){PlayerList.insert(this);}

        Player(int filler){};

        Player(std::string name, std::string style, int lvl = 1, int xp = 0)
        {
            if(style == "Bruiser")
                {
                    Name  = name;
                    Style = style;
                    HP    =  500 + 100*lvl;
                    MaxHP = HP;
                    STR   =  50 + 20*lvl;
                    SPD   = 10 + 2*lvl;
                    AP    = 40 + 10*lvl;
                    MaxAP = AP;
                    LVL   = lvl;
                    XP    = xp;
                }
            if(style == "Nimble")
                {
                    Name  = name;
                    Style = style;
                    HP    =  300 + 100*lvl;
                    MaxHP = HP;
                    STR   =  30 + 20*lvl;
                    SPD   = 20 + 2*lvl;
                    AP    = 30 + 10*lvl;
                    MaxAP = AP;
                    LVL   = lvl;
                    XP    = xp;
                }
            if(style == "Energetic")
                {
                    Name  = name;
                    Style = style;
                    HP    =  400 + 10*lvl;
                    MaxHP = HP;
                    STR   =  40 + 20*lvl;
                    SPD   = 15 + 2*lvl;
                    AP    = 50 + 10*lvl;
                    MaxAP = AP;
                    LVL   = lvl;
                    XP    = xp;
                }
            PlayerList.insert(this);

        }

        void setName(std::string name){Name = name;}

        virtual std::string getName(){return Name;}

        std::string getStyle(){return Style;}

        void setHP(int hp)
        {
            HP = hp;
            MaxHP = HP;
        }

        virtual int getHP(){return HP;}

        virtual int getMaxHP(){return MaxHP;}

        void setSTR(int str){STR = str;}

        virtual int getSTR(){return STR;}

        void setSPD(int spd){SPD = spd;}

        virtual int getSPD(){return SPD;}

        virtual void setAP(int ap)
        {
            AP = ap;
            MaxAP = ap;
        }

        virtual void UseAP(int ap){AP -= ap;}

        virtual int getAP(){return AP;}

        virtual int getMaxAP(){return MaxAP;}

        void setLVL(int lvl){LVL = lvl;}

        void LVLUP()
        {
            while(XP>LVL*200)
                {
                    if(LVL < MaxLVL && XP >= LVL*200)
                    {
                        XP    -= LVL*200;
                        LVL   += 1;
                        HP    += 100;
                        MaxHP += 100;
                        STR   += 20;
                        SPD   += 2;
                        AP    += 10;
                        MaxAP += 10;
                        std::cout << Name << " Has Leveled UP " << std::endl;
                        std::cout << "Level Is: " << LVL << std::endl;
                        std::cout << "HP Is: " << MaxHP << std::endl;
                        std::cout << "STR Is: " << STR << std::endl;
                        std::cout << "SPD Is: " << SPD << std::endl;
                        std::cout << "AP Is: " << MaxAP << std::endl;
                    }
                }
        }

        virtual int getLVL(){return LVL;}

        void setXP(int xp){XP = xp;}

        void AddXP(int xp)
        {
            std::cout << Name << " Gained " << xp << " XP" <<std::endl;
            XP +=xp;
            LVLUP();
        }

        int getXP(){return XP;}

        static std::set<Player*> getPlayerList(){return PlayerList;}

        void RestoreStats()
        {
            HP = MaxHP;
            AP = MaxAP;
        }

        void AddValidTarget(std::string Target){ValidTargets.insert(Target);}

        void ClearValidTarget(){ValidTargets.clear();}

        Player* CheckTarget(std::vector<Player*> ptrs, std::string TargetName)
        {
            for(auto ptr : ptrs)
                {
                    if(ptr->getName() == TargetName)
                        return ptr;
                }
        }

        virtual void AddSkill(Skill& ability)
        {
            int DupeCheck = 0;
            for(auto abi : Skills)
                {
                    if(abi.getName() == ability.getName())
                        DupeCheck++;
                }
            if(DupeCheck == 0)
                {
                    Skills.push_back(ability);
                    ValidActions.insert(ability.getName());
                }
        }

        virtual void AddStatusEffect(std::string status, std::string cure)
        {
            StatusEffects.insert(status);
            if(StatusEffects.count(cure))
            {
                StatusEffects.erase(cure);
                std::cout << "   " << this->getName() << "'s " << cure << " removed" << std::endl;
            }
        }

        virtual void RemoveStatusEffect(std::string status){StatusEffects.erase(status);}

        virtual std::set<std::string> getStatusEffects(){return StatusEffects;}

        void ProcStatus()
        {
            if(StatusEffects.count(Fire.getStatusEffect()))
                {
                    TakeDMG(10);
                    std::cout << "   " << this->getName() << " " << Fire.getStatusEffect() << "ED" << std::endl;
                    std::cout << "   " << "It Dealt " << 10 << " DMG" << std::endl;
                }

            if(HP > MaxHP) //Make Sure Healing Doesn't Exceed Max HP
                HP = MaxHP;
        }

        virtual int getTurnBar(){return TurnBar;}

        virtual void TakeDMG(int DMG){HP -= DMG;}

        virtual void TakeTurn(){TurnBar -= 100;}

        virtual void EndTurn(){TurnBar += SPD;}

        virtual void OnDeathStats(Player& obj, int lvl){}

        virtual void OnDeathSkills(Player& obj){}

        virtual void OnDeath(Player& obj, int lvl){}

        void GetSet(std::set<std::string> List)
        {
            for(std::set<std::string>::iterator itr = List.begin(); itr != List.end(); itr++)
                {
                    std::cout << *itr << " ";
                }
        }

        virtual void TakeAction(std::vector<Player*> players,int TargetCount)//Target count is only used in the derived class
        {
            std::cout << Name <<"'s TURN" << std::endl << "   ";

            std::cout << "Valid Actions : ";

            GetSet(ValidActions);

            std::cout << std::endl << "   ";

            std::cout << "Valid Targets : ";

            GetSet(ValidTargets);

            std::cout << std::endl << "   ";

            if(StatusEffects.count(Bash.getStatusEffect()))
                {
                    std::cout << "   " << this->getName() << " " << Bash.getStatusEffect() << "NED" << std::endl;
                    StatusEffects.erase(Bash.getStatusEffect());
                    return;
                }

            std::string Action, TargetName, Nothing;
            Player* Target;
            bool Valid = false;

            std::cout << "ENTER ACTION AND TARGET"   << std::endl << "   ";


            std::cin >> Action;
            std::cin >> TargetName;
            std::getline(std::cin,Nothing); // Takes care of extra inputs from ruining future inputs in case an invalid input was entered


            if(!ValidTargets.count(TargetName) || !ValidActions.count(Action))
                throw InvalidInputException();

            Target = CheckTarget(players,TargetName);

            if (Action == "Attack")
                {
                    Attack(Target);
                    Valid = true;
                }

            for(auto ability : Skills)
                {
                    if(Action == ability.getName() && AP > ability.getCost())
                        {
                            UseSkill(ability, Target);
                            Valid = true;
                            break;
                        }
                }

            if(!Valid)
                throw InsufficientAPException();

            ProcStatus();
        }

        void Attack(Player* ptr)
        {
            ptr->TakeDMG(getSTR());
            std::cout << "   " << this->getName() << " Attacked " << ptr->getName() << std::endl << "   ";
            std::cout << "It Dealt " << getSTR() << " DMG" << std::endl;
        }

        void UseSkill(Skill ability, Player* ptr)
        {
            ptr->TakeDMG((ability.getSTR()));
            this->UseAP(ability.getCost());
            std::cout << "   " << this->getName() << " Used " << ability.getName() << " on " << ptr->getName() << std::endl;
            std::cout << "   " << "It Dealt " << ability.getSTR() << " DMG" << std::endl;
            std::cout << "   " << "It Inflicted " << ability.getStatusEffect() << std::endl;
            ptr->AddStatusEffect(ability.getStatusEffect(),ability.getCure());
            std::cout << "   " << "AP IS: " << this->getAP() << std::endl;
        }

        static void SavePlayersBinary()
        {
            std::ofstream Players("Players.bin",std::ios::binary);
            if(!Players)
                {
                    std::cout<<"Error Opening File!!"<<std::endl;
                    return;
                }
            int PlayerCount = PlayerList.size();
            Players.write((char *) &PlayerCount,4);
            for(auto player : PlayerList)
                {
                    if(player->getName() != "Enemy")
                        {
                            std::string name = player->getName(), style = player->getStyle();
                            int hp = player->getHP(), str = player->getSTR(), spd = player->getSPD(), ap = player->getAP(), lvl = player->getLVL(), xp = player->getXP() ;
                            int NameSize = name.length(), HPSize = sizeof(hp), STRSize = sizeof(str), SPDSize = sizeof(spd), APSize = sizeof(ap), LVLSize = sizeof(lvl), XPSize = sizeof(xp), SkillCount = player->Skills.size();
                            Players.write((char *) &NameSize,4);
                            Players.write((char *) name.c_str(),NameSize);
                            Players.write((char *) &HPSize,4);
                            Players.write((char *) &hp,HPSize);
                            Players.write((char *) &STRSize,4);
                            Players.write((char *) &str,STRSize);
                            Players.write((char *) &SPDSize,4);
                            Players.write((char *) &spd,SPDSize);
                            Players.write((char *) &APSize,4);
                            Players.write((char *) &ap,APSize);
                            Players.write((char *) &LVLSize,4);
                            Players.write((char *) &lvl,LVLSize);
                            Players.write((char *) &XPSize,4);
                            Players.write((char *) &xp,XPSize);
                            Players.write((char *) &SkillCount,4);
                            for(auto skill : player->Skills)
                                {
                                    std::string SkillName = skill.getName();
                                    int SkillSize = SkillName.length();
                                    Players.write((char *) &SkillSize,4);
                                    Players.write((char *) SkillName.c_str(),SkillSize);
                                }
                        }

                }
            std::cout << "Data Saved Successfully !" << std::endl;
        }

        static void LoadPlayersBinary()
        {
            int hp, str, spd, ap, lvl, xp;
            int NameSize, HPSize, STRSize, SPDSize, APSize, LVLSize, XPSize, SkillSize, PlayerCount, SkillCount;

            std::ifstream Players("Players.bin",std::ios::binary);

            if(!Players)
                {
                    std::cout<<"Error Opening File!!"<<std::endl;
                    return;
                }
            Players.read((char *) &PlayerCount,4);

            Player* play = new Player[PlayerCount];

            for(int i = 0; i < PlayerCount; i++)
            {
                Players.read((char *) &NameSize,4);

                char* Namebuffer = new char[NameSize];

                Players.read((char *) Namebuffer,NameSize);

                std::string name(Namebuffer, NameSize);

                delete[] Namebuffer;

                play[i].setName(name);

                Players.read((char *) &HPSize,4);

                Players.read((char *) &hp,HPSize);

                play[i].setHP(hp);

                Players.read((char *) &STRSize,4);

                Players.read((char *) &str,STRSize);

                play[i].setSTR(str);

                Players.read((char *) &SPDSize,4);

                Players.read((char *) &spd,SPDSize);

                play[i].setSPD(spd);

                Players.read((char *) &APSize,4);

                Players.read((char *) &ap,APSize);

                play[i].setAP(ap);

                Players.read((char *) &LVLSize,4);

                Players.read((char *) &lvl,LVLSize);

                play[i].setLVL(lvl);

                Players.read((char *) &XPSize,4);

                Players.read((char *) &xp,XPSize);

                play[i].setXP(xp);

                Players.read((char *) &SkillCount,4);

                for(int j = 0; j < SkillCount; j++)
                    {
                        Players.read((char *) &SkillSize,4);

                        char* Skillbuffer = new char[SkillSize];

                        Players.read((char *) Skillbuffer,SkillSize);

                        std::string skill(Skillbuffer, SkillSize);

                        delete[] Skillbuffer;

                        for(auto Skill : Skill::getSkillList())
                            {
                                if(skill == Skill->getName())
                                    play[i].AddSkill(*Skill);
                            }
                    }
            }
           std::cout << "Data Loaded Successfully !" << std::endl;
        }
};

int Player::MaxLVL = 10;

std::set<Player*> Player::PlayerList;

bool operator == (Player  &obj1, Player  &obj2)
        {
            if(obj1.getName() == obj2.getName())
                return true;
            else
                return false;
        }

class Enemy : public Player
{
    private:
        Player AI;
        std::vector<Skill*> SkillDrops = {&Fire,&Water,&Wind,&Bash,&Heal};
        static int XPDrop;
    public:
        Enemy(std::string name, int hp, int str, int spd, int ap, int lvl) : Player(lvl)
        {
            AI.setName(name);
            AI.setHP(hp);
            AI.setSTR(str);
            AI.setSPD(spd);
            AI.setAP(ap);
            AI.setLVL(lvl);
        }

        std::string getName(){return AI.getName();}

        int getHP(){return AI.getHP();}

        int getMaxHP(){return AI.getMaxHP();}

        int getSTR(){return AI.getSTR();}

        int getSPD(){return AI.getSPD();}

        int getTurnBar(){return AI.getTurnBar();}

        void setAP(int ap){AI.setAP(ap);}

        void UseAP(int ap){AI.UseAP(ap);}

        int getAP(){return AI.getAP();}

        int getMaxAP(){return AI.getMaxAP();}

        void setLVL(int lvl){AI.setLVL(lvl);}

        int getLVL(){return AI.getLVL();}

        void AddSkill(Skill& ability){AI.AddSkill(ability);}

        void AddStatusEffect(std::string status, std::string cure){AI.AddStatusEffect(status,cure);}

        void RemoveStatusEffect(std::string status){AI.RemoveStatusEffect(status);}

        std::set<std::string> getStatusEffects(){return AI.getStatusEffects();}

        void TakeDMG(int DMG){AI.TakeDMG(DMG);}

        void TakeTurn(){AI.TakeTurn();}

        void EndTurn(){AI.EndTurn();}

        void OnDeathStats(Player& obj, int lvl) // Gives XP to the player scaling with the enemy's level
        {
            obj.AddXP(XPDrop*lvl);
        }

        void OnDeathSkill(Player& obj) //Adds a random skill to the player ; NOT GUARANTEED NEW
        {
            Skill SkillDrop = *SkillDrops[rand()%SkillDrops.size()];
            obj.AddSkill(SkillDrop);
            std::cout << obj.getName() << " Has Learned Skill : " << SkillDrop.getName() << std::endl;
        }

        void OnDeath(Player& obj, int lvl)
        {
            int chance = rand()%4;
            if(chance < 3) // 75% chance to get XP
                OnDeathStats(obj,lvl);
            else         // 25% cgabce to get a skill
                OnDeathSkill(obj);
        }

        void TakeAction(std::vector<Player*> ptrs,int TargetCount)
        {
            std::cout << AI.getName() <<"'s TURN" << std::endl;
            Player* ptr = ptrs[rand()%TargetCount];//pick random target from current alive Players
            if(AI.getStatusEffects().count(Bash.getStatusEffect()))
                {
                    std::cout << "   " << this->getName() << " " << Bash.getStatusEffect() << "NED" << std::endl;
                    AI.RemoveStatusEffect(Bash.getStatusEffect());
                    return;
                }

            else if(AI.getHP() >= (AI.getMaxHP()/2)) //PHASE 1,Just use skills
                {
                    int Decision = rand()%3;
                    if(Decision == 0)
                        Attack(ptr);
                    if(Decision == 1)
                        {
                            if(AI.getAP() >= Fire.getCost())
                                UseSkill(Fire,ptr);
                            else
                                Attack(ptr);
                        }
                    if(Decision == 2)
                       {
                            if(AI.getAP() >= Wind.getCost())
                                UseSkill(Wind,ptr);
                            else
                                Attack(ptr);
                       }
                }
            else if(AI.getHP() >= (AI.getMaxHP()/4))//PHASE 2, options that think of annoying situations
                {
                    int Decision = rand()%4;
                    if(Decision == 0)
                        Attack(ptr);
                    if(Decision == 1 || Decision == 2)
                        {
                            if(AI.getAP() >= Water.getCost() && AI.getStatusEffects().count(Fire.getStatusEffect()))// IF ON FIRE, USE WATER ON SELF
                                UseSkill(Water,this);
                            else if(AI.getAP() >= Fire.getCost())
                                UseSkill(Fire,ptr);
                            else
                                Attack(ptr);
                        }
                    if(Decision == 3)
                       {
                            if(AI.getAP() >= Heal.getCost())
                                UseSkill(Heal,this);
                            else
                                Attack(ptr);
                       }
                }
            else //PHASE 3, GO FULLY OFFENSIVE OR HEAL
                {
                    int Decision = rand()%3;
                    if(Decision == 0)
                        {
                            if(AI.getAP() >= Bash.getCost())
                                UseSkill(Bash,ptr);
                            else
                                Attack(ptr);
                        }
                    if(Decision == 1)
                        {
                            if(AI.getAP() >= Water.getCost() && AI.getStatusEffects().count(Fire.getStatusEffect()))// IF ON FIRE, USE WATER ON SELF
                                UseSkill(Water,this);
                            else if(AI.getAP() >= Fire.getCost())
                                UseSkill(Fire,ptr);
                            else
                                Attack(ptr);
                        }
                    if(Decision == 2)
                       {
                            if(AI.getAP() >= Heal.getCost())
                                UseSkill(Heal,this);
                            else
                                Attack(ptr);
                       }
                }
            AI.ProcStatus();
        }
};

int Enemy::XPDrop = 100;
Enemy Computer("Enemy",500,20,10,50,1);
Enemy Raid("Enemy",1000,40,20,100,1);

#endif // PLAYER_H_INCLUDED
