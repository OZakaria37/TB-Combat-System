#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

class Battle
{
    private:
        std::deque<Player*> TurnList;
        std::vector<Player*> Fighters;
        //Player *Other;
    public:
        Battle(Player* ptr1, Player* ptr2)
        {
            Fighters.push_back(ptr1);
            Fighters.push_back(ptr2);
        }

        Battle(Player* ptr1, Player* ptr2, Player* ptr3)
        {
            Fighters.push_back(ptr1);
            Fighters.push_back(ptr2);
            Fighters.push_back(ptr3);
        }

        void Add_To_TurnList(Player* ptr)
        {
            TurnList.push_back(ptr);
            ptr->TakeTurn();
        }

        bool ValidTurn()
        {
            if(TurnList.size() > 0 && TurnList[0]->getHP() > 0)
                return true;
            else if(TurnList.size() > 0 && TurnList[0]->getHP() <= 0)
                PopBattle();
            else
                return false;
        }

        std::deque<Player*> getTurnList()
        {
            //if( *TurnList[0] == *Fighters[0] )
               // Other = Fighters[1];
            //else
              //  Other = Fighters[0];
            return TurnList;
        }

        std::vector<Player*> getFighters(){return Fighters;}

        //Player* getOther(){return Other;}

        void PopFighters()
        {
            Fighters.erase(Fighters.begin());
        }

        void PopFightersIndex(int ind)
        {
            Fighters.erase(Fighters.begin()+ind);
        }

        void PopBattle()
        {
            TurnList.pop_front();
        }

        void EndTurn(std::vector<Player*> ptrs)
        {
            for(auto ptr : ptrs)
                {
                    ptr->EndTurn();
                    if(ptr->getTurnBar() >= 100)
                        Add_To_TurnList(ptr);
                }
        }
};

#endif // BATTLE_H_INCLUDED
