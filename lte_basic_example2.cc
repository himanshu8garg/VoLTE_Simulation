/*
 * Himanshu Garg, Evgeny Parasite 
 * This example is simple scenario where 1 eNB and 15 devices are there. 
 * Using constant position all UEs are situated.
 * this file generate an xml file using which we can simulate the scenario in NetAnim easily.
 */

#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/mobility-module.h>
#include <ns3/lte-module.h>
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/config-store-module.h"
using namespace ns3;

void
NotifyConnectionEstablishedUe (std::string context,
                               uint64_t imsi,
                               uint16_t cellid,
                               uint16_t rnti)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": connected to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyHandoverStartUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti,
                       uint16_t targetCellId)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": previously connected to CellId " << cellid
            << " with RNTI " << rnti
            << ", doing handover to CellId " << targetCellId
            << std::endl;
}

void
NotifyHandoverEndOkUe (std::string context,
                       uint64_t imsi,
                       uint16_t cellid,
                       uint16_t rnti)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " UE IMSI " << imsi
            << ": successful handover to CellId " << cellid
            << " with RNTI " << rnti
            << std::endl;
}

void
NotifyConnectionEstablishedEnb (std::string context,
                                uint64_t imsi,
                                uint16_t cellid,
                                uint16_t rnti)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": successful connection of UE with IMSI " << imsi
            << " RNTI " << rnti
            << std::endl;
}

void
NotifyHandoverStartEnb (std::string context,
                        uint64_t imsi,
                        uint16_t cellid,
                        uint16_t rnti,
                        uint16_t targetCellId)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": start handover of UE with IMSI " << imsi
            << " RNTI " << rnti
            << " to CellId " << targetCellId
            << std::endl;
}

void
NotifyHandoverEndOkEnb (std::string context,
                        uint64_t imsi,
                        uint16_t cellid,
                        uint16_t rnti)
{
  std::cout << Simulator::Now ().GetSeconds () << " " << context
            << " eNB CellId " << cellid
            << ": completed handover of UE with IMSI " << imsi
            << " RNTI " << rnti
            << std::endl;
}

int main (int argc, char *argv[])
{
    // the rest of the simulation program follows

  uint16_t numberOfUes = 20;
  uint16_t numberOfEnbs = 2;
  //uint16_t numBearersPerUe = 2;
  //double simTime = 0.300;
  double distance = 100.0;

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();

  //This will instantiate some common objects (e.g., the Channel object) and provide the methods to add eNBs and UEs and configure them.

  //Create Node objects for the eNB(s) and the UEs:

  NodeContainer enbNodes;
  enbNodes.Create (numberOfEnbs);
  NodeContainer ueNodes;
  ueNodes.Create (numberOfUes);

  //Note that the above Node instances at this point still don’t have an LTE protocol stack installed; they’re just empty nodes.

  //Configure the Mobility model for all the nodes:

//---------Set Mobility---------------------------------
  // Install Mobility Model
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  for (uint16_t i = 0; i < numberOfEnbs; i++)
    {
      positionAlloc->Add (Vector (distance * 2 * i - distance, 0, 0));
    }
  for (uint16_t i = 0; i < numberOfUes; i++)
    {
      positionAlloc->Add (Vector (0, 0, 0));
    }
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator (positionAlloc);
  mobility.Install (enbNodes);
  mobility.Install (ueNodes);
  //----------------------------------------------------

  // AnimationInterface::SetConstantPosition (enbNodes.Get (1), 10, 30);
   
    //AnimationInterface::SetConstantPosition (ueNodes.Get (0), 7, 1);
    //AnimationInterface::SetConstantPosition (ueNodes.Get (1), 5, 0);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (2), 5, 1);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (3), 5, 2);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (4), 5, 3);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (5), 5, 4);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (6), 5, 5);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (7), 5, 6);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (8), 5, 7);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (9), 5, 8);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (10), 5, 9);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (12), 5, 10);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (13), 3, 2);
    // AnimationInterface::SetConstantPosition (ueNodes.Get (14), 2, 3);

  //Install an LTE protocol stack on the eNB(s):

  NetDeviceContainer enbLteDevs;
  enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);

  //Install an LTE protocol stack on the UEs:

  NetDeviceContainer ueLteDevs;
  ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  //Attach the UEs to an eNB. This will configure each UE according to the eNB configuration, and create an RRC connection between them:
  //Attach all UEs to the first enB 

  //NS_LOG_LOGIC ("Attaching all UEs to the first enB");
  for (uint16_t i = 0; i < numberOfUes; i++)
    {
      lteHelper->Attach (ueLteDevs.Get (i), enbLteDevs.Get (0));
    }


  //Activate a data radio bearer between each UE and the eNB it is attached to:

  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  lteHelper->ActivateDataRadioBearer (ueLteDevs, bearer);

  //this method will also activate two saturation traffic generators for that bearer, one in uplink and one in downlink.
  //X2 based Handover added here 
  
  // lteHelper->AddX2Interface (enbNodes);
  // lteHelper->HandoverRequest (Seconds (0.100), ueLteDevs.Get (0), enbLteDevs.Get (0), enbLteDevs.Get (1));

  // Flow monitor
  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();


  //Set the stop time
  Simulator::Stop (Seconds (10));

  ///This is needed otherwise the simulation will last forever, because (among others) the start-of-subframe event is scheduled repeatedly, and the ns-3 simulator scheduler will hence never run out of events.
    lteHelper->EnablePhyTraces ();
    lteHelper->EnableMacTraces ();
    lteHelper->EnableRlcTraces ();
    lteHelper->EnablePdcpTraces ();

  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (0.05)));
  Ptr<RadioBearerStatsCalculator> pdcpStats = lteHelper->GetPdcpStats ();
  pdcpStats->SetAttribute ("EpochDuration", TimeValue (Seconds (0.05)));


  // connect custom trace sinks for RRC connection establishment and handover notification
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/ConnectionEstablished",
                   MakeCallback (&NotifyConnectionEstablishedEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/ConnectionEstablished",
                   MakeCallback (&NotifyConnectionEstablishedUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverStart",
                   MakeCallback (&NotifyHandoverStartEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/HandoverStart",
                   MakeCallback (&NotifyHandoverStartUe));
  Config::Connect ("/NodeList/*/DeviceList/*/LteEnbRrc/HandoverEndOk",
                   MakeCallback (&NotifyHandoverEndOkEnb));
  Config::Connect ("/NodeList/*/DeviceList/*/LteUeRrc/HandoverEndOk",
                   MakeCallback (&NotifyHandoverEndOkUe));
  //Run the simulation:
    AnimationInterface anim ("lte_animation_test.xml");
    anim.SetMobilityPollInterval(Seconds(0.05));
    anim.EnablePacketMetadata(true);
    Simulator::Run ();

    //flowMonitor->SerializeToXmlFile("NameOfFile.xml", true, true);
  //Cleanup and exit:

  Simulator::Destroy ();
  return 0;
}

