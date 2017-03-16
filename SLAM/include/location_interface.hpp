
//Created by Emerson Udy

#pragma once
namespace slam{

	class LocationInterface{
		public:
		TelemetryPacket getCurrentTelemetry();
		
		private:
		void getframe();//get frame from the IFrame stream
		void sendFrametoDSO();//Send frame to the DSOcollector	
		
		
	};
	

}