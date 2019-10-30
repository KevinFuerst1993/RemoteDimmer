//Includes
#include "Fsm.h"
#include "Webserver.h"
#include "Gpio.h"
#include "Timer.h"
/*
void test(void *pArg);
int testArg = 0;
 Gpio gpio(Gpio::D6, Gpio::output);
*/
void setup() 
{
  //Test-----------------
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Program started");
  //--------------------
}

void loop() 
{
  //Webserver webserver("FMBK-NG","Die21Tulpen");
  Webserver webserver("MySpot","123456789");
  Fsm fsm(&webserver);
/*
  Timer timer;
  timer.setInterval(3);
  timer.registerCb(test);
  timer.setRepeatMode(true);
  timer.start();
  */
 
  
  while(1)
  {
    webserver.handleClient(); 
  }
}

/*
void test(void *pArg)
{
  if(testArg == 0)
  {
    testArg = 1;
    gpio.setOutput(Gpio::high);
  }
  else
  {
    testArg = 0;
    gpio.setOutput(Gpio::low);
  }
}

                                                                                        
                                      Thepathof                                         
                                  therighteousmanis                                     
                              besetonallsidesbytheiniq                                  
                      uitiesoftheself           ishandth                                
                   etyrannyofevi                  lmen.Bl                               
                 essedishewho,in                   thenam                               
                 eofcharityandgoo                   dwill                               
                 ,shepherdst heweak    throughthev  alley                               
                 ofdarkness,forheist rulyhisbrother' skee                               
                 perandthefinderof  lostchildren.AndIwill                               
                strik  edownuponth  eewithgreatvengeancea                               
               ndfuriousangerthosew howouldatte mpttopois                               
              onanddestroyMybroth   ers.AndyouwillknowMyn                               
             ameistheLordwhenIlayMyvengeanceupont  hee.T                                
            hepat          hoftherighteousman     isbese                                
           tonal                      lsidesb     ythein                                
          iquiti                                 esofth                                 
         eselfi                                 shandt                                  
        hetyra                                  nnyofe                                  
        vilme                      n.Bl        essedi                                   
        shew                      ho,in the   nameof                                    
        char                      ityandgood  will,                         shepherds   
       thewe                      akthrough  theva                        lleyofdarkne  
       ss,fo                     rheistruly hisbr                       other'    skee  
       peran                     dthefinde  roflo                     stchild    ren.A  
       ndIwi                    llstriked  ownupo                   ntheewi     thgre   
       atven                    geancean   dfuriousangerthosewh   owoulda     ttemp     
        ttop                   oisonand    destroyMybrothers.Andyouwill      knowM      
        ynam                   eistheL     ordwh   enIla   yMyvengean      ceupon       
        thee                  .Thepath      oft   herighteousmanisb      eseton         
        allsi               desby thein         iquitiesoftheselfi     shandth          
         etyr             annyo  fevilme         n.Blessedishewho,in   thenameo         
         fchar            ityandgoodwill                     ,shepher    dstheweak      
          throu            ghthevalleyo              fdar       kness,  forh eistr      
          ulyhis              brot                   her'        skeepe  randthef       
           indero                                flo              stchi    ldre         
            n.AndIwi                            llst              riked     ownu        
               ponthee                          with              greatvengeance        
     and        furiousang                       erth           osewhowouldatte         
    mpttopo    isonanddestroyMyb                  rot         hers.An    d              
    youwillknowMyn ameistheLordwhenIlayM           yven    geanceu                      
    pont hee.Thepathoft    herighteousmani sbesetonallsidesbythe                        
     iniq  uitiesofth         eselfishand thetyrannyofevilmen                           
      .Ble   ssedis         hewho,inthen ameof charityandg                              
       oodwill,sh           epherdsthew  eakt                                           
        hrought              hevalley   ofda                                            
          rkn                ess,fo    rhei                                             
                              struly  hisb                                              
                               rother'ske                                               
                                 eperand                                                
                                   the 
                                
  */
