#include <iostream>
#include <deque>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>
#include <algorithm>
#include <fstream>
#include "Skill.h"
#include "Player.h"
#include "Battle.h"

using namespace std;

PVE(Player& Player,Enemy Computer)
{
    string Anything;//Does Nothing ; just to take input and end game
    Battle Fight(&Player,&Computer);
    bool Ongoing = true;
    Player.ClearValidTarget();
    for(auto fighter : Fight.getFighters())
        {
            Player.AddValidTarget(fighter->getName());
        }
    while(Ongoing)
        {
            bool Valid = false;
            if(Fight.getFighters()[0]->getHP() <= 0)
                {
                    cout << Fight.getFighters()[0]->getName() << " DIED" << endl;
                    cout << "YOU LOSE" << endl;
                    Fight.getFighters()[0]->RestoreStats();
                    cout << "Input Anything To Continue" << endl;
                    cin >> Anything;
                    break;
                }

            if(Fight.getFighters()[1]->getHP() <= 0)
                {
                    cout << "YOU WIN" << endl;
                    Fight.getFighters()[1]->OnDeath(*Fight.getFighters()[0],Player.getLVL());
                    Fight.getFighters()[0]->RestoreStats();
                    cout << "Input Anything To Continue" << endl;
                    cin >> Anything;
                    break;
                }

            if(Fight.ValidTurn())
                {
                    while(!Valid)
                    {
                        try
                            {
                                Fight.getTurnList()[0]->TakeAction(Fight.getFighters(),1);
                            }
                        catch(InvalidInputException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        catch(InsufficientAPException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        Valid = true;
                        Fight.PopBattle();
                    }
                }

            Fight.EndTurn(Fight.getFighters());
        }
}

PVP(Player Player1,Player Player2)
{
    Battle Fight(&Player1,&Player2);
    bool Ongoing = true;
    Player1.ClearValidTarget();
    Player2.ClearValidTarget();
    for(auto fighter : Fight.getFighters())
        {
            Player1.AddValidTarget(fighter->getName());
            Player2.AddValidTarget(fighter->getName());
        }
    while(Ongoing)
        {
            string Anything;//Does Nothing ; just to take input and end game
            bool Valid = false;
            if(Fight.getFighters()[0]->getHP() <= 0)
                {
                    cout << Fight.getFighters()[0]->getName() << " DIED" << endl;
                    cout << Fight.getFighters()[1]->getName() << " WON" << endl;
                    cout << "Input Anything To Continue" << endl;
                    cin >> Anything;
                    break;
                }

            if(Fight.getFighters()[1]->getHP() <= 0)
                {
                    cout << Fight.getFighters()[1]->getName() << " DIED" << endl;
                    cout << Fight.getFighters()[0]->getName() << " WON" << endl;
                    cout << "Input Anything To Continue" << endl;
                    cin >> Anything;
                    break;
                }

            if(Fight.ValidTurn())
                {
                    while(!Valid)
                    {
                        try
                            {
                                Fight.getTurnList()[0]->TakeAction(Fight.getFighters(),1);
                            }
                        catch(InvalidInputException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        catch(InsufficientAPException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        Valid = true;
                        Fight.PopBattle();
                    }
                }

            Fight.EndTurn(Fight.getFighters());
        }
}

COOP(Player& Player1,Player& Player2 ,Enemy Computer)
{
    string Anything;//Does Nothing ; just to take input and end game
    Battle Fight(&Player1,&Player2, &Computer);
    int allies = 2, P1Death = 0, P2Death = 0;
    bool Ongoing = true;

    while(Ongoing)
        {
            Player1.ClearValidTarget();
            Player2.ClearValidTarget();
            for(auto fighter : Fight.getFighters())
            {
                Player1.AddValidTarget(fighter->getName());
                Player2.AddValidTarget(fighter->getName());
            }

            bool Valid = false;



            if(Player1.getHP() <= 0 && P1Death == 0)
                {
                    cout << Player1.getName() << " DIED" << endl;
                    Fight.PopFighters();
                    P1Death++;
                    allies--;
                    if(allies == 0)
                    {
                        Player1.RestoreStats();
                        Player2.RestoreStats();
                        cout << "YOU LOSE" << endl;
                        cout << "Input Anything To Continue" << endl;
                        cin >> Anything;
                        break;
                    }
                }
            if(Player2.getHP() <= 0 && P2Death == 0)
                {
                    cout << Player2.getName() << " DIED" << endl;
                    if(P1Death == 1)
                        Fight.PopFightersIndex(0);
                    else
                        Fight.PopFightersIndex(1);
                    P2Death++;
                    allies--;
                    if(allies == 0)
                    {
                        Player1.RestoreStats();
                        Player2.RestoreStats();
                        cout << "YOU LOSE" << endl;
                        cout << "Input Anything To Continue" << endl;
                        cin >> Anything;
                        break;
                    }
                }

            if(Fight.getFighters()[Fight.getFighters().size() -1 ]->getHP() <= 0)
                {
                    cout << Fight.getFighters()[Fight.getFighters().size() -1]->getName() << " DIED" << endl;
                    cout << "YOU WIN" << endl;
                    Fight.getFighters()[Fight.getFighters().size() -1]->OnDeath(Player1,Player1.getLVL());
                    Fight.getFighters()[Fight.getFighters().size() -1]->OnDeath(Player2,Player2.getLVL());
                    Player1.RestoreStats();
                    Player2.RestoreStats();
                    cout << "Input Anything To Continue" << endl;
                    cin >> Anything;
                    break;
                }

            if(Fight.ValidTurn())
                {
                    while(!Valid)
                    {
                        try
                            {
                                Fight.getTurnList()[0]->TakeAction(Fight.getFighters(),allies);
                            }
                        catch(InvalidInputException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        catch(InsufficientAPException& Except)
                            {
                                cout << "   " << Except.what();
                                cout << "   TRY AGAIN" << endl;
                                continue;
                            }
                        Valid = true;
                        Fight.PopBattle();
                    }
                }

            Fight.EndTurn(Fight.getFighters());
        }
}

CreateNewPlayer()
{
    std::string Name, Style;
    bool validName = false, validStyle = false;

    cout << "Please Enter Your Name" << endl;

    while(!validName)
        {
            cin >> Name;
            if(Name == "Enemy")
                cout << "   Cannot Name Character Enemy "<< endl << "   TRY AGAIN" << endl;
            else
                validName = true;
        }

    cout << "Please Pick Style : " << endl;
    cout << "   Bruiser    : Has More STR But Less SPD And Medium AP" << endl;
    cout << "   Nimble     : Has Less STR But More SPD And Low AP" << endl;
    cout << "   Energetic  : Has Mid STR But Mid SPD And High AP" << endl;

    while(!validStyle)
        {
            cin >> Style;

            if(Style == "Bruiser" || Style == "Nimble" || Style == "Energetic" )
                validStyle = true;
            else
                cout << "   Invalid Style "<< endl << "   TRY AGAIN" << endl;
        }

        Player* play = new Player(Name,Style,1);
}

int main()
{
    srand(time(0));
    std::string Choice, Anything;
    bool Ongoing = true;
    Computer.AddSkill(Fire);
    Computer.AddSkill(Water);
    Computer.AddSkill(Wind);
    Computer.AddSkill(Bash);
    Computer.AddSkill(Heal);
    Raid.AddSkill(Fire);
    Raid.AddSkill(Water);
    Raid.AddSkill(Wind);
    Raid.AddSkill(Bash);
    Raid.AddSkill(Heal);
    while(Ongoing)
        {
            system("cls");
            cout << "                                          Welcome To Omar Ahmed Gamal Zakaria's Project" << endl;
            cout << "Please Choose Action: " << endl;
            cout << "   New  : Creates New Character" << endl;
            cout << "   PVE  : Battle The Computer for XP and Skills" << endl;
            cout << "   PVP  : Battle The Another Player" << endl;
            cout << "   COOP : Battle The Computer for XP and Skills With The Help Of Another Player" << endl;
            cout << "   Save : Save Character Data" << endl;
            cout << "   Load : Load Last Saved Character Data" << endl;
            cout << "   Tut  : Show System Explanation" << endl;
            cout << "   Cred : Show Credits For The Project" << endl;
            cout << "   exit : exit program" << endl;
            cin >> Choice;

            if(Choice == "New")
            {
                system("cls");
                CreateNewPlayer();
                cout << "Character Created Successfully" <<endl;
                cout << "Input Anything to return to Main Menu" <<endl;
                cin >> Anything;
            }

           else if(Choice == "PVE")
            {
                system("cls");

                if(Player::getPlayerList().size() < 3)// 2 Enemies Exist in the List by default
                    {
                        cout << "Not Enough Characters Exist" << endl;
                        cout << "Try Loading or Creating New Characters" << endl;
                        cout << "Input Anything To Return To Menu" << endl;
                        cin >> Anything;
                    }
                else
                    {
                        std::string name, Nothing;
                        bool valid = false;
                        cout << "Please Pick a Character From The List"<<endl;
                        for(auto play : Player::getPlayerList())
                            {
                                if(play->getName() != "Enemy")
                                    cout << play->getName() << " ";
                            }

                        cout << endl;

                        while(!valid)
                            {
                                cout << "Enter Valid Input :" << endl;
                                cin >> name;
                                getline(std::cin,Nothing);
                                for(auto player : Player::getPlayerList())
                                    {
                                        if(name == player->getName() && "Enemy" != player->getName())
                                            {
                                                cout << "Character Loaded !" << endl;
                                                cout << "Input Anything To Start Fight" << endl;
                                                cin >> Anything;
                                                system("cls");
                                                PVE(*player,Computer);
                                                valid = true;
                                                break;
                                            }
                                    }
                            }
                    }
            }

            else if(Choice == "PVP")
                {
                    system("cls");

                    if(Player::getPlayerList().size() < 5)// 2 Enemies Exist in the List by default, 1 extra Enemy on loading for a total of 3
                    {
                        cout << "Not Enough Characters Exist" << endl;
                        cout << "Try Loading or Creating New Characters" << endl;
                        cout << "Input Anything To Return to Menu" << endl;
                        cin >> Anything;
                    }
                    else
                        {
                            std::string name1, name2, Nothing;
                            int Enter = 0;
                            bool valid = false;
                            cout << "Please Pick 2 Characters From List"<<endl;
                            for(auto play : Player::getPlayerList())
                                {
                                    if(play->getName() != "Enemy")
                                        cout << play->getName() << " ";
                                }

                            cout << endl;

                            while(!valid)
                                {
                                    cout << "Enter Valid Input :" << endl;
                                    cin >> name1 >> name2;
                                    getline(std::cin,Nothing);
                                    for(auto player1 : Player::getPlayerList())
                                        {
                                            for(auto player2 : Player::getPlayerList())
                                                {
                                                    if(Enter == 0 && name1 == player1->getName() && name2 == player2->getName() && "Enemy" != player1->getName() && "Enemy" != player2->getName())
                                                        {
                                                            Enter++;
                                                            cout << "Characters Loaded !" << endl;
                                                            cout << "Input Anything To Start Fight" << endl;
                                                            cin >> Anything;
                                                            system("cls");
                                                            PVP(*player1,*player2);
                                                            valid = true;
                                                            break;
                                                        }
                                                }
                                        }
                                }
                        }
                }
            else if(Choice == "COOP")
                {
                    system("cls");

                    if(Player::getPlayerList().size() < 5)// 2 Enemies Exist in the List by default, 1 extra Enemy on loading for a total of 3
                    {
                        cout << "Not Enough Characters Exist" << endl;
                        cout << "Try Loading or Creating New Characters" << endl;
                        cout << "Input Anything To Return to Menu" << endl;
                        cin >> Anything;
                    }
                    else
                        {
                            std::string name1, name2,Nothing;
                            int Enter = 0;
                            bool valid = false;
                            cout << "Please Pick 2 Characters From List"<<endl;
                            for(auto play : Player::getPlayerList())
                                {
                                    if(play->getName() != "Enemy")
                                        cout << play->getName() << " ";
                                }

                            cout << endl;

                            while(!valid)
                                {
                                    cout << "Enter Valid Input :" << endl;
                                    cin >> name1 >> name2;
                                    getline(std::cin,Nothing);
                                    for(auto player1 : Player::getPlayerList())
                                        {
                                            for(auto player2 : Player::getPlayerList())
                                                {
                                                    if(Enter == 0 && name1 == player1->getName() && name2 == player2->getName() && "Enemy" != player1->getName() && "Enemy" != player2->getName())
                                                        {
                                                            Enter++;
                                                            cout << "Characters Loaded !" << endl;
                                                            cout << "Input Anything To Start Fight" << endl;
                                                            cin >> Anything;
                                                            system("cls");
                                                            COOP(*player1,*player2,Raid);
                                                            valid = true;
                                                            break;
                                                        }
                                                }
                                        }
                                }
                        }
                }

            else if(Choice == "Save")
                {
                    system("cls");
                    Player::SavePlayersBinary();
                    cout << "Input Anything to return to Main Menu" <<endl;
                    cin >> Anything;
                }

            else if(Choice == "Load")
                {
                    system("cls");
                    Player::LoadPlayersBinary();
                    cout << "Input Anything to return to Main Menu" <<endl;
                    cin >> Anything;
                }
            else if(Choice == "Tut")
                {
                    system("cls");
                    cout << "Below Are Simple Instructions For The Systems :" << endl;
                    cout << "   HP Increases Amount Of Damage That Can Be Taken" << endl;
                    cout << "   STR Increases Damage Dealt" << endl;
                    cout << "   SPD Increases Rate Of Getting Turns" << endl;
                    cout << "   AP Increases Amount Of Possible Skill Uses" << endl;
                    cout << "   XP Increases LVL" << endl;
                    cout << "   LVL Increases All Other Stats" << endl;
                    cout << "   Fire Adds Burn to Enemies, Which Does DMG/Turn And Removes And Prevents Wet" << endl;
                    cout << "   Water Adds Wet, Which Removes And Prevents Burn" << endl;
                    cout << "   Wind Adds Dry, Which Removes And Prevents Wet" << endl;
                    cout << "   Bash Adds Stun, Which Wastes The Next Turn" << endl;
                    cout << "   Heal Does -DMG And Restores HP" << endl;
                    cout << "   You Are Able To Target Anyone In The Valid Target List; Including Yourself" << endl;
                    cout << "   Every Non PVP Game Mode Gives either XP Or A Random Skill" << endl;
                    cout << "   Have Fun Playing :)" << endl;
                    cout << "Input Anything to return to Main Menu" <<endl;
                    cin >> Anything;
                }
            else if(Choice == "Cred")
                {
                    system("cls");
                    cout << "This Project Was Solely Made By :" << endl;
                    cout << "   Name : Omar Ahmed Gamal Zakaria" << endl;
                    cout << "   ID   : 19104756" << endl;
                    cout << "   Special Thanks To : Omar Ahmed Gamal Zakaria's Efforts And Contributions To This Project" << endl;
                    cout << "Input Anything to return to Main Menu" <<endl;
                    cin >> Anything;
                }

            else if(Choice == "exit")
            {
                system("cls");
                cout << "Come Play Again :)" << endl;
                break;
            }
        }

    return 0;
}
