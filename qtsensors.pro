TEMPLATE = subdirs

module_qtsensors_src.subdir = src
module_qtsensors_src.target = module-qtsensors-src

module_qtsensors_tests.subdir = tests
module_qtsensors_tests.target = module-qtsensors-tests
module_qtsensors_tests.depends = module_qtsensors_src
!contains(QT_BUILD_PARTS,tests) {
    module_qtsensors_tests.CONFIG = no_default_target no_default_install
}

SUBDIRS += module_qtsensors_src \
           module_qtsensors_tests
