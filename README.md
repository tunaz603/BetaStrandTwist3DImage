# BetaStrandTwist3DProteinImage
Analysis of ß-strand Twist from the 3-dimensional Image of a Protein

Description: 

Electron cryo-microscopy (Cryo-EM) technique produces density maps that are 3-dimensional (3D) images of molecules. It is challenging to derive atomic structures of proteins from 3D images of medium resolutions. Twist of a β-strand has been studied extensively while little of the known information has been directly obtained from the 3D image of a β-sheet. We describe a method to characterize the twist of β-strands from the 3D image of a protein. An analysis of 11 β-sheet images shows that the Averaged Minimum Twist (AMT) angle is larger for a close set than for a far set of β-traces.

Here is the Publication link of our paper: https://dl.acm.org/citation.cfm?id=3107507

You can read the pdf from my website: https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnx0dW5hemlzbGFtfGd4OjJkMmZkNzRlNWNlZjFlYmY


HOW TO RUN:
--------------------------------------------------------------------------------

STRAND_CROP:
--------------------------------------------------------------------------------
The strand_crop tool runs in all subdirectories, and generates a cropped version
of all .pdb files of the following form:
s1.pdb
s2.pdb
s3.pdb
sX.pdb

By "cropped", we mean the pdb file, which should represent a strand curve,
will be downsampled such that all samples are within a certain distance of each
other. The accuracy of the crop depends on how high the resolution of the input
data is.

The base C program only takes in a single data stream from standard input, and 
outputs a data stream representing a cropped version. We use a family of shell 
scripts to provide interaction with the file system.


HOW TO RUN GENERATE_DATA:
--------------------------------------------------------------------------------
The strand_crop executable provided as well as the corresponding shell scripts
are meant to be run on Linux only.

The strand crop tool takes in three parameters:

./generate_data <sampling_length> <starting_index> <data_set_name>


sampling_length: Desired amount of Angstroms each sample will be distributed by.

starting_index:  Which line we begin to sample points.  If this is zero, 
				     sampling will start on the first line.

data_set_name:   What the output filename will be appended with after the 
                     program runs.

For example:

./generate_data.sh 1.5 6 data_set_6

Will generate the following files:

s1.pdb_data_set_6.pdb
s2.pdb_data_set_6.pdb
s3.pdb_data_set_6.pdb
sX.pdb_data_set_6.pdb

HOW TO RUN REMOVE_DATA:
--------------------------------------------------------------------------------
As well, we provide a utility script that removes all files of a specific data
set, to be used if a data set generated is no longer needed, or was generated in
error.  For example,

./remove_data.sh data_set_6

Will remove the following files:

s1.pdb_data_set_6.pdb
s2.pdb_data_set_6.pdb
s3.pdb_data_set_6.pdb
sX.pdb_data_set_6.pdb

COMPILING STRAND_CROP
--------------------------------------------------------------------------------
To compile the C source code, run the following line in the console:

./make.sh


TWIST ANGLES:
--------------------------------------------------------------------------------
1) Use putty or any ssh 

2) keep necessary folders in a directory.

	For Image we have this folder "Image_sampling_skip8" (as we skip 8 points for image)
	
  For True case we have three folders named "true skip_0", "true skip_1", "true skip_2"

3) go to that directory writing "cd" command
   
    cd "type the path  here"
	
   For image each protein folder has two different folders named "good" and "bad":
   
   For example : For good case of 1d1t protein image
   
   cd "/home/tislam/Image_sampling_skip8/1dtd/good"
	
   
   For True case: 
  
   For example : For true case of 1d1t protein 
   
   cd "/home/tislam/Image_sampling_skip8/true skip_0/TrueCase/1dtd"

4) For image we used several input files according to the number of strands 

	For example: s1.pdb_data8.pdb, s2.pdb_data8.pdb,.............................(As we skip 8 points for image)
	
   For true case we used several input files according to the number of strands and skipping points 

	For example: 
  
         s1.pdb, s2.pdb,............................. (if we skip nothing)
	
	 s1.pdb_data1.pdb, s2.pdb_data1.pdb,.............................(if we skip 1 point)
	
	 s1.pdb_data2.pdb, s2.pdb_data2.pdb,.............................(if we skip 2 points)
   
5) To run the code 

	python filename.py
	
	For image :
	 
   for example: python twist_image_0_30.py 
	
  For true case :
	 
   for example: python twist_true_1dtd.py 

6) Output file will be generated in current directory as a name of "twist_angles.txt".

  Inside output files you can see the details of twist angles.
	
  for example: twist angle between two neighbouring strands, avg. twist angles between two neighbouring strands,
	as well as avg. twist angles of 2 longest strands
