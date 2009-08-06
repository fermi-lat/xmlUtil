# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/xmlUtil/xmlUtilLib.py,v 1.1 2008/07/09 21:13:48 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['xmlUtil'])
    env.Tool('xmlBaseLib')
    env.Tool('facilitiesLib')
    env.Tool('addLibrary', library = env['xercesLibs'])

def exists(env):
    return 1;
