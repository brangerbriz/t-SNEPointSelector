import sys, os, glob, shutil, csv, time

if len(sys.argv) == 2:

	lmd_dir    = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'lmd_mono_tracks_seperated')
	output_dir = os.path.join('knn_searches', os.path.splitext(os.path.basename(sys.argv[1]))[0])
	knn_csv    = sys.argv[1]

	with open(knn_csv, 'r') as f:
	    reader = csv.DictReader(f)
	    neighbors = [row['neighbor_id'] for row in reader if row['distance'] != '0']

	# delete dirname if it exists
	if os.path.isdir(output_dir):
	    shutil.rmtree(output_dir)

	# create dirname if it doesn't exist
	if not os.path.isdir(output_dir):
	    os.mkdir(output_dir)

	files = [os.path.join(lmd_dir, filename) for filename in neighbors]
	for f in files:
	    os.link(f, os.path.join(output_dir, os.path.basename(f)))
	print('created {} symlinks in {}'.format(len(files), output_dir))
else:
	print('CSV path must be specified as the first and only argument.')
	exit(1)