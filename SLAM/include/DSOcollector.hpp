#pragma once

namespace slam {

	class DSOcollector
	{
	public:
		DSOcollector();
		~DSOcollector();
		TelemetryPacket getTelemetryPacket();
	};

}