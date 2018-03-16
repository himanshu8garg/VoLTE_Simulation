#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/config-store-module.h"
using namespace ns3;
int main (int argc, char *argv[])
{
	CommandLine cmd;
	cmd.Parse (argc, argv);
	ConfigStore inputConfig;
	inputConfig.ConfigureDefaults ();
	cmd.Parse (argc, argv);
	Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
	lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisSpectrumPropagationLossModel"));
	
	NodeContainer enbNodes;
	NodeContainer ueNodes;
	
	enbNodes.Create (1);
	ueNodes.Create (3);
	
	MobilityHelper mobility;
	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility.Install (enbNodes);
	mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	mobility.Install (ueNodes);
	
	NetDeviceContainer enbDevs;
	NetDeviceContainer ueDevs;
	
	enbDevs = lteHelper->InstallEnbDevice (enbNodes);
	ueDevs = lteHelper->InstallUeDevice (ueNodes);
	lteHelper->Attach (ueDevs, enbDevs.Get (0));
	
	enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
	EpsBearer bearer (q);
	
	lteHelper->ActivateDataRadioBearer (ueDevs, bearer);
	
	Simulator::Stop (Seconds (0.5));
	
	lteHelper->EnablePhyTraces ();
	lteHelper->EnableMacTraces ();
	lteHelper->EnableRlcTraces ();
	
	double distance_temp [] = { 1000,1000,1000};
	std::vector<double> userDistance;
	userDistance.assign (distance_temp, distance_temp + 3);
	for (int i = 0; i < 3; i++)
	{
	Ptr<ConstantPositionMobilityModel> mm = ueNodes.Get (i)->GetObject<ConstantPositionMobilityModel> ();
	mm->SetPosition (Vector (userDistance[i], 0.0, 0.0));
	}


	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
