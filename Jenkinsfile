// List of targets to compile
def targets = [
  //"LPC1768",
  //"NUCLEO_F401RE",
  //"NRF51822",
  "K64F"
  ]

// Map toolchains to compiler labels on Jenkins
def toolchains = [
  //ARM: "armcc",
  //IAR: "iar_arm",
  GCC_ARM: "arm-none-eabi-gcc"
  ]

// Initial maps for parallel build steps
def stepsForParallel = [:]

// Jenkins pipeline does not support map.each, we need to use oldschool for loop
for (int i = 0; i < targets.size(); i++) {
  for(int j = 0; j < toolchains.size(); j++) {
    def target = targets.get(i)
    def toolchain = toolchains.keySet().asList().get(j)
    def compilerLabel = toolchains.get(toolchain)

    def stepName = "${target} ${toolchain}"
    stepsForParallel[stepName] = buildStep(target, compilerLabel, toolchain)
  }
}

/* Jenkins does not allow stages inside parallel execution,
* https://issues.jenkins-ci.org/browse/JENKINS-26107 will solve this by adding labeled blocks
*/
stage "build mbed-cloud-client-example targets"
// Actually run the steps in parallel - parallel takes a map as an argument, hence the above.
parallel stepsForParallel


/* End of execution, internal functions below */

def execute(cmd) {
    if (isUnix()) {
        sh "${cmd}"
    } else {
        bat "${cmd}"
    }
}

//Create build steps for parallel execution
def buildStep(target, compilerLabel, toolchain) {
  return {
    node ("${compilerLabel}") {
      deleteDir()
      dir("mbed-cloud-client-example") {
        checkout scm
        execute ("mbed deploy --protocol ssh")
        execute ("mbed compile -m ${target} -t ${toolchain} -DSTORAGE_DRIVER_CONFIG_HARDWARE_MTD_ASYNC_OPS=0 -DDEVICE_STORAGE_CONFIG_HARDWARE_MTD_K64F_ASYNC_OPS=0 -DMBEDTLS_PEM_WRITE_C -c")
      }
    }
  }
}
