/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

#include "sources/Team.hpp" //no need for other includes
#include "sources/SmartTeam.hpp"

using namespace ariel;

int main()
{

   {
      // brawling and camping:

      // initializing team Left:
      OldNinja *lCaptain = new OldNinja("LCaptain", {100, -100});
      OldNinja *Lon1 = new OldNinja("Lon1", {90, -100});
      YoungNinja *Lyn1 = new YoungNinja("Lyn1", {80, -100});
      YoungNinja *Lyn2 = new YoungNinja("Lyn2", {70, -100});
      TrainedNinja *Ltn1 = new TrainedNinja("Ltn1", {60, -100});
      TrainedNinja *Ltn2 = new TrainedNinja("Ltn2", {50, -100});
      Cowboy *Lc1 = new Cowboy("Lc1", {40, -100});
      Cowboy *Lc2 = new Cowboy("Lc2", {30, -100});
      Cowboy *Lc3 = new Cowboy("Lc3", {20, -100});
      Cowboy *Lc4 = new Cowboy("Lc4", {10, -100});

      SmartTeam leftTeam(lCaptain);
      leftTeam.add(Lon1);
      leftTeam.add(Lyn1);
      leftTeam.add(Lyn2);
      leftTeam.add(Ltn1);
      leftTeam.add(Ltn2);
      leftTeam.add(Lc1);
      leftTeam.add(Lc2);
      leftTeam.add(Lc3);
      leftTeam.add(Lc4);

      // initializing team Right:
      OldNinja *rCaptain = new OldNinja("RCaptain", {100, 100});
      OldNinja *Ron1 = new OldNinja("Ron1", {90, 100});
      YoungNinja *Ryn1 = new YoungNinja("Ryn1", {80, 100});
      YoungNinja *Ryn2 = new YoungNinja("Ryn2", {70, 100});
      TrainedNinja *Rtn1 = new TrainedNinja("Rtn1", {60, 100});
      TrainedNinja *Rtn2 = new TrainedNinja("Rtn2", {50, 100});
      Cowboy *Rc1 = new Cowboy("Rc1", {40, 100});
      Cowboy *Rc2 = new Cowboy("Rc2", {30, 100});
      Cowboy *Rc3 = new Cowboy("Rc3", {20, 100});
      Cowboy *Rc4 = new Cowboy("Rc4", {10, 100});

      Team rightTeam(rCaptain);
      rightTeam.add(Ron1);
      rightTeam.add(Ryn1);
      rightTeam.add(Ryn2);
      rightTeam.add(Rtn1);
      rightTeam.add(Rtn2);
      rightTeam.add(Rc1);
      rightTeam.add(Rc2);
      rightTeam.add(Rc3);
      rightTeam.add(Rc4);

      while (leftTeam.stillAlive() > 0 && rightTeam.stillAlive() > 0)
      {
         leftTeam.attack(&rightTeam);
         rightTeam.attack(&leftTeam);
         leftTeam.print();
         rightTeam.print();
      }
      //
      if (leftTeam.stillAlive() > 0)
         cout << "winner is leftTeam" << endl;
      else
         cout << "winner is rightTeam" << endl;
   }


   // {
   //    //rushing: 

   //    // initializing team Left:
   //    OldNinja *lCaptain = new OldNinja("LCaptain", {100, -10});
   //    OldNinja *Lon1 = new OldNinja("Lon1", {90, -10});
   //    YoungNinja *Lyn1 = new YoungNinja("Lyn1", {80, -10});
   //    YoungNinja *Lyn2 = new YoungNinja("Lyn2", {70, -10});
   //    TrainedNinja *Ltn1 = new TrainedNinja("Ltn1", {60, -10});
   //    TrainedNinja *Ltn2 = new TrainedNinja("Ltn2", {10, -10});

   //    SmartTeam leftTeam(lCaptain);
   //    leftTeam.add(Lon1);
   //    leftTeam.add(Lyn1);
   //    leftTeam.add(Lyn2);
   //    leftTeam.add(Ltn1);
   //    leftTeam.add(Ltn2);
      

   //    // initializing team Right:
   //    OldNinja *rCaptain = new OldNinja("RCaptain", {50, 10});
   //    YoungNinja *Ryn1 = new YoungNinja("Ryn1", {80, 10});
   //    Cowboy *Rc1 = new Cowboy("Rc1", {40, 10});
   //    Cowboy *Rc2 = new Cowboy("Rc2", {30, 10});
   //    Cowboy *Rc3 = new Cowboy("Rc3", {20, 10});
   //    Cowboy *Rc4 = new Cowboy("Rc4", {10, 10});

   //    Team rightTeam(rCaptain);
   //    rightTeam.add(Ryn1);
   //    rightTeam.add(Rc1);
   //    rightTeam.add(Rc2);
   //    rightTeam.add(Rc3);
   //    rightTeam.add(Rc4);

   //    while (leftTeam.stillAlive() > 0 && rightTeam.stillAlive() > 0)
   //    {
   //       leftTeam.attack(&rightTeam);
   //       rightTeam.attack(&leftTeam);
   //       leftTeam.print();
   //       rightTeam.print();
   //    }
   //    //
   //    if (leftTeam.stillAlive() > 0)
   //       cout << "winner is leftTeam" << endl;
   //    else
   //       cout << "winner is rightTeam" << endl;
   // }

   return 0;

   
}
