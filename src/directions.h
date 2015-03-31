#include <pebble.h>
#pragma once

#include <pebble.h>

#define NUM_CLOCK_TICKS 11
#define NUM_BT_LINES 9
#define NUM_BAT_LINES_TOTAL 10	
#define NUM_BAT_LINES 10	
static const struct GPathInfo ANALOG_BG_POINTS[] = 
{
	//12
	{ 4,
    	(GPoint[]) 
    	{
			{68, 0},
      		{71, 0},
      		{71, 6},
      		{68, 6}
    	}
  	},
  	{ 4, 
  		(GPoint [])
  		{
  	    	{72, 0},
  	    	{75, 0},
  	    	{75, 6},
  	    	{72, 6}
  	  	}
  	},
  	
  	//1
  	{ 4, 
  		(GPoint [])
  		{							
			{112, 10},
  	    	{114, 12},
  	    	{108, 23},
  	    	{106, 21}
  	  	}
  	},
  	
	//2
  	{ 4, 
  		(GPoint [])
  		{
  		    {132, 47},
  		    {144, 40},
  		    {144, 44},
  		    {135, 49}
  		}
  	},
  	
  	//4
  	{ 4, 
  		(GPoint [])
  		{
  		    {135, 118},
  		    {144, 123},
  		    {144, 126},
  		    {132, 120}
  		}
  	},
  	
  	//5
  	{ 4, 
  		(GPoint [])
  		{
  		    {108, 144},
  		    {114, 154},
  		    {112, 157},
  		    {106, 147}
  		}
  	},
  	
  	//6
  	{ 4, 
  		(GPoint [])
  		{
  		    {70, 161},
			{73, 161},
  		    {73, 167},
  		    {70, 167}
  		}
  	},
  	
  	//7
  	{ 4, 
  		(GPoint [])
  		{
  		    {32, 10},
  		    {30, 12},
  		    {36, 23},
  		    {38, 21}
  		}
  	},
  	
  	//8
  	{ 4, 
  		(GPoint [])
  		{
  		    {12, 47},
  		    {-1, 40},
  		    {-1, 44},
  		    {9, 49}
  		}
  	},
  	
  	//10
  	{ 4, 
  		(GPoint [])
  		{
  		    {9, 118},
  		    {-1, 123},
  		    {-1, 126},
  		    {12, 120}
  		}
  	},
  	
  	//11
  	{ 4, 
  		(GPoint [])
  		{
  		    {36, 144},
  		    {30, 154},
  		    {32, 157},
  		    {38, 147}
  		}
  	},

};

static const GPathInfo MINUTE_HAND_POINTS =
{ 3,
  	(GPoint []) 
  	{
    	{ -8, 20 },
    	{ 8, 20 },
    	{ 0, -80 }
	}
};

static const GPathInfo HOUR_HAND_POINTS = 
{ 3, 
	(GPoint [])
	{
    	{-6, 20},
    	{6, 20},
    	{0, -60}
  	}
};

static const struct GPathInfo BLUETOOTH_POINTS[] = 
{
  	{ 2, 
  		(GPoint [])
  		{
  	    	{5, 4},
  	    	{5, 13}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{5, 4},
  	    	{8, 7}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{8, 7},
  	    	{7, 8}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{7, 8},
  	    	{4, 8}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{4, 8},
  	    	{2, 6}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{5, 13},
  	    	{8, 10}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{8, 10},
  	    	{7, 9}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{7, 9},
  	    	{4, 9}
  	  	}
  	},
	
  	{ 2, 
  		(GPoint [])
  		{
  	    	{4, 9},
  	    	{2, 11}
  	  	}
  	}	
};

static const struct GPathInfo BATTERY_POINTS[] = 
{
  	{ 4, 
  		(GPoint [])
  		{
  	    	{126, 4},
  	    	{126, 11},
  	    	{140, 11},
  	    	{140, 4}
  	  	}
  	},

	{ 2, 
  		(GPoint [])
  		{
  	    	{141, 6},
  	    	{141, 9}
  	  	}
  	},

	{ 2, 
  		(GPoint [])
  		{
  	    	{128, 6},
  	    	{128, 9}
  	  	}
  	},
	{ 2, 
  		(GPoint [])
  		{
  	    	{129, 6},
  	    	{129, 9}
  	  	}
  	},

	{ 2, 
  		(GPoint [])
  		{
  	    	{131, 6},
  	    	{131, 9}
  	  	}
  	},
	{ 2, 
  		(GPoint [])
  		{
  	    	{132, 6},
  	    	{132, 9}
  	  	}
  	},

	{ 2, 
  		(GPoint [])
  		{
  	    	{134, 6},
  	    	{134, 9}
  	  	}
  	},
	{ 2, 
  		(GPoint [])
  		{
  	    	{135, 6},
  	    	{135, 9}
  	  	}
  	},
		
	{ 2, 
  		(GPoint [])
  		{
  	    	{137, 6},
  	    	{137, 9}
  	  	}
  	},
	{ 2, 
  		(GPoint [])
  		{
  	    	{138, 6},
  	    	{138, 9}
  	  	}
  	}

};
