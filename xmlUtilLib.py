# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/xmlUtil/xmlUtilLib.py,v 1.2 2009/08/06 23:59:48 jrb Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['xmlUtil'])
	if env['PLATFORM'] == 'win32':
	    env.Tool('findPkgPath', package = 'xmlUtil') 
    env.Tool('xmlBaseLib')
    env.Tool('facilitiesLib')
    env.Tool('addLibrary', library = env['xercesLibs'])

def exists(env):
    return 1;
