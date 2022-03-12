import os
import platform
import sys

if platform.system() == "Windows":
	import win32clipboard
else:
	from subprocess import Popen , PIPE


def getEffectOrExit() -> str:

	if len( sys.argv ) != 2:
		exit()

	return sys.argv[ 1 ]


def getClipboards() -> [ str ]:

	if platform.system() == "Windows":

		win32clipboard.OpenClipboard()
		return [ win32clipboard.GetClipboardData( win32clipboard.CF_UNICODETEXT ) ]

	elif platform.system() == "Linux":

		process = Popen( [ 'xsel' , '-bo' ] , stdout=PIPE )
		clipboard = process.communicate()[0].decode()
		process = Popen( [ 'xsel' , '-po' ] , stdout=PIPE )
		primary = process.communicate()[0].decode()
		process = Popen( [ 'xsel' , '-so' ] , stdout=PIPE )
		secondary = process.communicate()[0].decode()
		return [ clipboard , primary , secondary ]

	return None


def applyEffect( text: str , effect: str ) -> str:

	if not text:
		return None
	elif effect == "uppercase":
		return text.upper()
	elif effect == "lowercase":
		return text.lower()
	elif effect == "normalizePath":
		return os.path.normpath( text )
	elif effect == "escapeBackslash":
		return text.replace( "\\" , "\\\\" )
	elif effect == "unescapeBackslash":
		return text.replace( "\\\\" , "\\" )
	elif effect == "backslashes":
		return text.replace( "/" , "\\" )
	elif effect == "forwardSlashes":
		return text.replace( "\\" , "/" )

	return text


def setClipboards( texts: [ str ] ) -> None:

	if not texts:
		return

	if platform.system() == "Windows":

		win32clipboard.EmptyClipboard()
		win32clipboard.SetClipboardText( texts[ 0 ] )
		win32clipboard.CloseClipboard()
		return

	for index , text in enumerate( texts ):

		if not text:
			continue
		elif index == 0:
			process = Popen( [ 'xsel' , '-bi' ] , stdin=PIPE )
		elif index == 1:
			process = Popen( [ 'xsel' , '-pi' ] , stdin=PIPE )
		elif index == 2:
			process = Popen( [ 'xsel' , '-si' ] , stdin=PIPE )

		process.communicate( input=text.encode() )


# main

effect = getEffectOrExit()
texts = getClipboards()

if texts:
	for index , text in enumerate( texts ):
		texts[ index ] = applyEffect( text , effect )

setClipboards( texts )
