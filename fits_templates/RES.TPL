################################################################################
# TEST TEMPLATE FILE FOR PIMP OUTPUT EVENT LIST
#
################################################################################

XTENSION	BINTABLE	/ Binary table extension
EXTNAME		SNGLEVENT	/ Single events
EXTREL		'3.0'		/ Template Version
TELESCOP	INTEGRAL	/ Telescope or mission name
ORIGIN		PIMP		/ Origin of FITS file
INSTRUME	SPI		/ Instrument name
CREATOR		String		/ Program that created this FITS file
CONFIGUR	String		/ Software configuration
DATE		UTC_format	/ FITS file creation date
TTYPE#	        PRIME_E		/ Energy fired
TFORM#  	1E		/ Single precision
TTYPE#	        E_DEP		/ Energy deposit
TFORM#	        1E		/ Single precision
TTYPE#	        DETECTOR	/ Detector ID
TFORM#	        1I		/ Integer
TTYPE#	        EVENT		/ Event ID
TFORM#	        1J		/ Long integer

XTENSION	BINTABLE	/ Binary table extension
EXTNAME		MLTEVENT	/ Multiple events
EXTREL		'3.0'		/ Template Version
TELESCOP	INTEGRAL	/ Telescope or mission name
ORIGIN		PIMP		/ Origin of FITS file
INSTRUME	SPI		/ Instrument name
CREATOR		String		/ Program that created this FITS file
CONFIGUR	String		/ Software configuration
DATE		UTC_format	/ FITS file creation date
TTYPE#	        PRIME_E		/ Energy fired
TFORM#  	1E		/ Single precision
TTYPE#	        E_DEP		/ Energy deposit
TFORM#	        1E		/ Single precision
TTYPE#	        DETECTOR	/ Detector ID
TFORM#	        1I		/ Integer
TTYPE#	        EVENT		/ Event ID
TFORM#	        1J		/ Long integer
