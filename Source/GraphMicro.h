#pragma once
#define GFX_THROW(hr) if(FAILED((hr))) throw(Graph::HrException(__LINE__,__FILE__,(hr))) 