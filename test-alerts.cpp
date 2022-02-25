#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") 
{
  REQUIRE(inferBreach(19, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
  REQUIRE(inferBreach(0, 0, 15) == NORMAL);
  REQUIRE(inferBreach(-1, 0, 15) == TOO_LOW);
  REQUIRE(inferBreach(-5, -20, -5) == NORMAL);
  REQUIRE(inferBreach(-4, -20, -5) == TOO_HIGH);
  REQUIRE(inferBreach(0., -0.1, 0.1) == NORMAL);
  REQUIRE(inferBreach(-1.2, -1.1, -0.5) == TOO_LOW);
  REQUIRE(inferBreach(-0.4, -1.1, -0.5) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits of each coolingType") 
{
  //Test PASSIVE_COOLING limits
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, PASSIVE_COOLING_LOW_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, PASSIVE_COOLING_LOW_LIMIT - 0.1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, PASSIVE_COOLING_HIGH_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, PASSIVE_COOLING_HIGH_LIMIT + 0.1) == TOO_HIGH);
  //Test HI_ACTIVE_COOLING limits
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, HI_ACTIVE_COOLING_LOW_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, HI_ACTIVE_COOLING_LOW_LIMIT - 0.1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, HI_ACTIVE_COOLING_HIGH_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, HI_ACTIVE_COOLING_HIGH_LIMIT + 0.1) == TOO_HIGH);
  //Test MED_ACTIVE_COOLING limits
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, MED_ACTIVE_COOLING_LOW_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, MED_ACTIVE_COOLING_LOW_LIMIT - 0.1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, MED_ACTIVE_COOLING_HIGH_LIMIT) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, MED_ACTIVE_COOLING_HIGH_LIMIT + 0.1) == TOO_HIGH);
}

TEST_CASE("print to verify sending an alert to the controller") 
{
  sendToController(NORMAL);
  sendToController(TOO_LOW);
  sendToController(TOO_HIGH);
}

TEST_CASE("print to verify sending an alert through email") 
{
  sendToEmail(NORMAL);
  sendToEmail(TOO_LOW);
  sendToEmail(TOO_HIGH);
}

TEST_CASE("print to verify check and alert feature") 
{
  //Test sending alerts to the controller. Verify corresponding printing.
  // Test PASSIVE_COOLING
  BatteryCharacter batteryChar1 = {PASSIVE_COOLING, "BatteryPassiveNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar1, PASSIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar2 = {PASSIVE_COOLING, "BatteryPassiveLow"};
  checkAndAlert(TO_CONTROLLER, batteryChar2, PASSIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar3 = {PASSIVE_COOLING, "BatteryPassiveNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar3, PASSIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar4 = {PASSIVE_COOLING, "BatteryPassiveHigh"};
  checkAndAlert(TO_CONTROLLER, batteryChar4, PASSIVE_COOLING_HIGH_LIMIT + 0.1);
  // Test HI_ACTIVE_COOLING
  BatteryCharacter batteryChar5 = {HI_ACTIVE_COOLING, "BatteryHiActNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar5, HI_ACTIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar6 = {HI_ACTIVE_COOLING, "BatteryHiActLow"};
  checkAndAlert(TO_CONTROLLER, batteryChar6, HI_ACTIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar7 = {HI_ACTIVE_COOLING, "BatteryHiActNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar7, HI_ACTIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar8 = {HI_ACTIVE_COOLING, "BatteryHiActHigh"};
  checkAndAlert(TO_CONTROLLER, batteryChar8, HI_ACTIVE_COOLING_HIGH_LIMIT + 0.1);
  // Test MED_ACTIVE_COOLING
  BatteryCharacter batteryChar9 = {MED_ACTIVE_COOLING, "BatteryMedActNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar9, MED_ACTIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar10 = {MED_ACTIVE_COOLING, "BatteryMedActLow"};
  checkAndAlert(TO_CONTROLLER, batteryChar10, MED_ACTIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar11 = {MED_ACTIVE_COOLING, "BatteryMedActNormal"};
  checkAndAlert(TO_CONTROLLER, batteryChar11, MED_ACTIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar12 = {MED_ACTIVE_COOLING, "BatteryMedActHigh"};
  checkAndAlert(TO_CONTROLLER, batteryChar12, MED_ACTIVE_COOLING_HIGH_LIMIT + 0.1);

  //Test sending alerts through email. Verify corresponding printing.
  // Test PASSIVE_COOLING
  BatteryCharacter batteryChar13 = {PASSIVE_COOLING, "BatteryPassiveNormal"};
  checkAndAlert(TO_EMAIL, batteryChar13, PASSIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar14 = {PASSIVE_COOLING, "BatteryPassiveLow"};
  checkAndAlert(TO_EMAIL, batteryChar14, PASSIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar15 = {PASSIVE_COOLING, "BatteryPassiveNormal"};
  checkAndAlert(TO_EMAIL, batteryChar15, PASSIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar16 = {PASSIVE_COOLING, "BatteryPassiveHigh"};
  checkAndAlert(TO_EMAIL, batteryChar16, PASSIVE_COOLING_HIGH_LIMIT + 0.1);
  // Test HI_ACTIVE_COOLING
  BatteryCharacter batteryChar17 = {HI_ACTIVE_COOLING, "BatteryHiActNormal"};
  checkAndAlert(TO_EMAIL, batteryChar17, HI_ACTIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar18 = {HI_ACTIVE_COOLING, "BatteryHiActLow"};
  checkAndAlert(TO_EMAIL, batteryChar18, HI_ACTIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar19 = {HI_ACTIVE_COOLING, "BatteryHiActNormal"};
  checkAndAlert(TO_EMAIL, batteryChar19, HI_ACTIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar20 = {HI_ACTIVE_COOLING, "BatteryHiActHigh"};
  checkAndAlert(TO_EMAIL, batteryChar20, HI_ACTIVE_COOLING_HIGH_LIMIT + 0.1);
  // Test MED_ACTIVE_COOLING
  BatteryCharacter batteryChar21 = {MED_ACTIVE_COOLING, "BatteryMedActNormal"};
  checkAndAlert(TO_EMAIL, batteryChar21, MED_ACTIVE_COOLING_LOW_LIMIT);
  BatteryCharacter batteryChar22 = {MED_ACTIVE_COOLING, "BatteryMedActLow"};
  checkAndAlert(TO_EMAIL, batteryChar22, MED_ACTIVE_COOLING_LOW_LIMIT - 0.1);
  BatteryCharacter batteryChar23 = {MED_ACTIVE_COOLING, "BatteryMedActNormal"};
  checkAndAlert(TO_EMAIL, batteryChar23, MED_ACTIVE_COOLING_HIGH_LIMIT);
  BatteryCharacter batteryChar24 = {MED_ACTIVE_COOLING, "BatteryMedActHigh"};
  checkAndAlert(TO_EMAIL, batteryChar24, MED_ACTIVE_COOLING_HIGH_LIMIT + 0.1);
}
