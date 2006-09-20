#!/usr/bin/env python
import sys
OCTETS_PER_LINE = 16

def convert( outstream, instream ):
	writtenBytes = 0
	while True:
		byte = instream.read(1)
		if len(byte) != 1:
			break
		outstream.write( "0x%.2x, " % ord(byte) )
		writtenBytes += 1
		if writtenBytes % OCTETS_PER_LINE == 0:
			outstream.write( "\n" )
	message = "\n\n/* Size = %i bytes */\n" % writtenBytes
	outstream.write( message )

if __name__ == '__main__':
	if len(sys.argv) == 1:
		instream = sys.stdin
		outstream = sys.stdout
		if sys.platform == "win32":
			import os,msvcrt
			msvcrt.setmode(sys.stdin.fileno(), os.O_BINARY)
	elif len(sys.argv) == 3:
		instream = file(sys.argv[1],'rb')
		outstream = file(sys.argv[2], 'wt')
	else:
		print "Usage: bin2c [infile outfile]"
		print "\tIf no filenames are given, read from stdin and out"
		print "\tOn windows, invoke through python.exe if redirecting"
		print "\tinput and output since pipes are broken on win32."
		sys.exit(0)
	convert(outstream, instream)
	sys.exit(0)
