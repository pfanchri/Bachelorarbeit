
#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int main(void)
{
  // DAVE_STATUS_t status;

  //status = DAVE_Init();           /* Initialization of DAVE APPs  */

  //if(status == DAVE_STATUS_FAILURE)


  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 0, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 0);


  XMC_GPIO_SetMode(XMC_GPIO_PORT1, 1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
    XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 1);

while (1){
    for(int i=0; i<500000; i++ ) XMC_GPIO_SetOutputHigh(XMC_GPIO_PORT1, 0);

    for(int j=0; j<500000; j++ ) XMC_GPIO_SetOutputLow(XMC_GPIO_PORT1, 0);
}

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {


  }
}
