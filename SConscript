# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/xmlUtil/SConscript,v 1.11 2012/01/11 19:06:20 jrb Exp $
# Authors: Joanne Bogart <jrb@slac.stanford.edu>
# Version: xmlUtil-03-04-05
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='xmlUtil', toBuild='shared')
xmlUtil = libEnv.SharedLibrary('xmlUtil',
                               ['src/Arith.cxx', 'src/Substitute.cxx',
                                'src/Constants.cxx', 'src/Source.cxx',
                                'src/id/DictConstraints.cxx',
                                'src/id/DictField.cxx', 'src/id/DictFieldMan.cxx',
                                'src/id/DictNode.cxx','src/id/DictValidVisitor.cxx',
                                'src/id/IdConversion.cxx','src/id/IdConverter.cxx',
                                'src/id/IdDict.cxx', 'src/id/IdDictMan.cxx',
                                'src/id/Identifier.cxx', 'src/id/IdOpCompress.cxx',
                                'src/id/IdOpTruncate.cxx','src/id/IdOperation.cxx',
                                'src/id/NamedId.cxx', 'src/id/IdKey.cxx',
                                'src/docMan/GDDDocMan.cxx'])

progEnv.Tool('xmlUtilLib')
byId_test = progEnv.Program('byId_test',[ 'src/byId_test/byId_test.cxx'])
arith_test = progEnv.Program('arith_test',[ 'src/arith_test/arith_test.cxx'])

eval = progEnv.Program('eval', ['src/eval.cxx', 'src/local/outUtils.cxx'])
forProg = progEnv.Program('forProg', ['src/makeXmlForProg.cxx',
                                      'src/local/outUtils.cxx'])
forDoc = progEnv.Program('forDoc', ['src/makeXmlForDoc.cxx',
                                    'src/local/outUtils.cxx'])

testId = progEnv.Program('testId',[ 'src/id/testId.cxx'])
testDocMan = progEnv.Program('testDocMan',[ 'src/docMan/test_docMan.cxx'])
testKey = progEnv.Program('testKey', ['src/id/testKey.cxx'])

progEnv.Tool('registerTargets', package = 'xmlUtil',
             libraryCxts = [[xmlUtil, libEnv]],
             testAppCxts = [[byId_test,progEnv], [arith_test,progEnv]],
             binaryCxts = [[eval,progEnv], [forProg, progEnv],
                           [forDoc, progEnv], [testId, progEnv],
                           [testDocMan, progEnv], [testKey, progEnv]],
             includes = listFiles(['xmlUtil/*'], recursive = 1))




