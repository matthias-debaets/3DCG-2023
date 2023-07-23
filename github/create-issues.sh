if [[ `which gh` == "" ]]; then
	if uname -a | grep -i msys; then
		PATH="$PATH:/c/Program Files/GitHub CLI"
		if [[ `which gh` == "" ]]; then
			echo "GitHub CLI not found. Install here: https://cli.github.com/"
			exit
		else
			echo "GitHub CLI found in default install folder."
		fi
	else
		echo "GitHub CLI not found. Install here: https://cli.github.com/"
		exit
	fi
fi

URL=`git remote -v | grep origin | grep push | awk '{print($2)}'`
ORG=`echo $URL | cut -d/ -f4`
REPONAME=`echo $URL | cut -d/ -f5 | sed s/\.git//`
REPO="$ORG/$REPONAME"

ID_QUERY='
query getProject($org: String!, $repo: String!) {
	repository(name: $repo, owner: $org) {
		projectsV2(first: 1) {
			nodes {
				id
			}
		}
	}
}'

PROJECT_ID=`gh api graphql -f org="$ORG" -f repo="$REPONAME" -f query="$ID_QUERY" |  grep -oP '(?<="id":)".+"(?=\})'`

if [[ $? != 0 ]]; then
	echo "You may be missing the required permissions."
	echo "Please run \`gh auth refresh --scopes project\` in a capable terminal."
	exit
fi

if [[ $PROJECT_ID == "" ]]; then
	echo "Couldn't find a project associated with this repository."
	exit
fi

add_issue () {
	echo "Adding issue $1..."
	local ISSUE_URL=`gh issue create --title "$1" --label enhancement --body $2 -R $REPO`
	local ISSUE_NUMBER=`echo $ISSUE_URL | cut -d/ -f7`
	local ISSUE_QUERY='
	query getProject($org: String!, $repo: String!, $issue: Int!) {
		repository(name: $repo, owner: $org) {
			issue(number: $issue) {
				id
			}
		}
	}'
	# might fail if we go too fast, so slow down a bit
	sleep 1
	local ISSUE_ID=`gh api graphql -f org="$ORG" -f repo="$REPONAME" -F issue="$ISSUE_NUMBER" -f query="$ISSUE_QUERY" |  grep -oP '(?<="id":)".+"(?=\})'`
	# initial get might fail, so repeat until it works
	while [[ $ISSUE_ID == "" ]]; do
		sleep 1
		echo "Getting issue ID failed, retrying..."
		ISSUE_ID=`gh api graphql -f org="$ORG" -f repo="$REPONAME" -F issue="$ISSUE_NUMBER" -f query="$ISSUE_QUERY" |  grep -oP '(?<="id":)".+"(?=\})'`
	done
	gh api graphql -f project="$PROJECT_ID" -f item="$ISSUE_ID" -f query='
	mutation AddToProject($project: ID!, $item: ID!) {
		addProjectV2ItemById(input: { projectId: $project, contentId: $item }) {
			item {
				id
			}
		}
	}'
	if [[ $? != 0 ]]; then
		echo "You may be missing the required permissions."
		echo "Please run \`gh auth refresh --scopes project\` in a capable terminal."
		exit
	fi
}

echo hello
exit

add_issue "Bouncy and Elastic Animation" http://3dcg.leone.ucll.be/extensions/animations/bounce-elastic/explanations.html
add_issue "Circular Animation" http://3dcg.leone.ucll.be/extensions/animations/circular/explanations.html
add_issue "Easing Library" http://3dcg.leone.ucll.be/extensions/animations/easing-library/explanations.html
add_issue "Lissajous Animation" http://3dcg.leone.ucll.be/extensions/animations/lissajous/explanations.html
add_issue "Animation Operations" http://3dcg.leone.ucll.be/extensions/animations/operations/explanations.html
add_issue "Polynomial Easing Functions" http://3dcg.leone.ucll.be/extensions/animations/polynomial-easing/explanations.html
add_issue "Depth of Field Camera" http://3dcg.leone.ucll.be/extensions/cameras/depth-of-field/explanations.html
add_issue "Fisheye Camera" http://3dcg.leone.ucll.be/extensions/cameras/fisheye/explanations.html
add_issue "Orthographic Camera" http://3dcg.leone.ucll.be/extensions/cameras/orthographic/explanations.html
add_issue "MaterialProperties Default Values Redundancy" http://3dcg.leone.ucll.be/extensions/improvements/material-properties-defaults/explanations.html
add_issue "Translucency Optimization" http://3dcg.leone.ucll.be/extensions/improvements/translucency/explanations.html
add_issue "Scripting" http://3dcg.leone.ucll.be/extensions/introduction/scripting/explanations.html
add_issue "Area Lights" http://3dcg.leone.ucll.be/extensions/lights/area-light/explanations.html
add_issue "Directional Light" http://3dcg.leone.ucll.be/extensions/lights/directional-light/explanations.html
add_issue "Spot Lights" http://3dcg.leone.ucll.be/extensions/lights/spot-lights/explanations.html
add_issue "Marble" http://3dcg.leone.ucll.be/extensions/materials/marble/explanations.html
add_issue "Pattern Materials" http://3dcg.leone.ucll.be/extensions/materials/pattern/explanations.html
add_issue "Textures" http://3dcg.leone.ucll.be/extensions/materials/texture/explanations.html
add_issue "Material Transformation" http://3dcg.leone.ucll.be/extensions/materials/transformations/explanations.html
add_issue "Worley 2D" http://3dcg.leone.ucll.be/extensions/materials/worley/explanations.html
add_issue "Perlin" http://3dcg.leone.ucll.be/extensions/math/perlin/explanations.html
add_issue "Quaternions" http://3dcg.leone.ucll.be/extensions/math/quaternions/explanations.html
add_issue "Transformations" http://3dcg.leone.ucll.be/extensions/math/transformations/explanations.html
add_issue "Voronoi" http://3dcg.leone.ucll.be/extensions/math/voronoi/explanations.html
add_issue "Basics" http://3dcg.leone.ucll.be/extensions/patterns/basics/explanations.html
add_issue "Dalmatian Pattern" http://3dcg.leone.ucll.be/extensions/patterns/dalmatian/explanations.html
add_issue "Flower Pattern" http://3dcg.leone.ucll.be/extensions/patterns/flower/explanations.html
add_issue "Lambda Pattern" http://3dcg.leone.ucll.be/extensions/patterns/lambda/explanations.html
add_issue "Logic Operations" http://3dcg.leone.ucll.be/extensions/patterns/logic-operations/explanations.html
add_issue "Spiral Pattern" http://3dcg.leone.ucll.be/extensions/patterns/spiral/explanations.html
add_issue "Tiling" http://3dcg.leone.ucll.be/extensions/patterns/tiling/explanations.html
add_issue "Pattern Transformations" http://3dcg.leone.ucll.be/extensions/patterns/transformations/explanations.html
add_issue "Balanced Parallel Task Scheduler" http://3dcg.leone.ucll.be/extensions/performance/balanced-parallel-task-scheduler/explanations.html
add_issue "Naive Parallel Task Scheduler" http://3dcg.leone.ucll.be/extensions/performance/naive-parallel-task-scheduler/explanations.html
add_issue "Unbalanced Parallel Task Scheduler" http://3dcg.leone.ucll.be/extensions/performance/unbalanced-parallel-task-scheduler/explanations.html
add_issue "Motion Blur" http://3dcg.leone.ucll.be/extensions/pipeline/motion-blur/explanations.html
add_issue "Studio Pipeline Segment" http://3dcg.leone.ucll.be/extensions/pipeline/studio/explanations.html
add_issue "Binary Mesh" http://3dcg.leone.ucll.be/extensions/primitives/binary-mesh/explanations.html
add_issue "Bounding Box Accelerator" http://3dcg.leone.ucll.be/extensions/primitives/bounding-box-accelerator/explanations.html
add_issue "Box" http://3dcg.leone.ucll.be/extensions/primitives/box/explanations.html
add_issue "Bumpifier" http://3dcg.leone.ucll.be/extensions/primitives/bumpifier/explanations.html
add_issue "Coarse" http://3dcg.leone.ucll.be/extensions/primitives/coarse/explanations.html
add_issue "Cone" http://3dcg.leone.ucll.be/extensions/primitives/cone/explanations.html
add_issue "Cropper" http://3dcg.leone.ucll.be/extensions/primitives/cropper/explanations.html
add_issue "Constructive Solid Geometry" http://3dcg.leone.ucll.be/extensions/primitives/csg/explanations.html
add_issue "Cylinder" http://3dcg.leone.ucll.be/extensions/primitives/cylinder/explanations.html
add_issue "Disk" http://3dcg.leone.ucll.be/extensions/primitives/disk/explanations.html
add_issue "Mesh" http://3dcg.leone.ucll.be/extensions/primitives/mesh/explanations.html
add_issue "Planes" http://3dcg.leone.ucll.be/extensions/primitives/plane/explanations.html
add_issue "Resizer" http://3dcg.leone.ucll.be/extensions/primitives/resizer/explanations.html
add_issue "Smooth Mesh" http://3dcg.leone.ucll.be/extensions/primitives/smooth-mesh/explanations.html
add_issue "Textured Mesh" http://3dcg.leone.ucll.be/extensions/primitives/textured-mesh/explanations.html
add_issue "Transformations" http://3dcg.leone.ucll.be/extensions/primitives/transformations/explanations.html
add_issue "Triangle" http://3dcg.leone.ucll.be/extensions/primitives/triangle/explanations.html
add_issue "Ray Tracer v1" http://3dcg.leone.ucll.be/extensions/ray-tracers/v1/explanations.html
add_issue "Ray Tracer v2" http://3dcg.leone.ucll.be/extensions/ray-tracers/v2/explanations.html
add_issue "Ray Tracer v3" http://3dcg.leone.ucll.be/extensions/ray-tracers/v3/explanations.html
add_issue "Ray Tracer v4" http://3dcg.leone.ucll.be/extensions/ray-tracers/v4/explanations.html
add_issue "Ray Tracer v5" http://3dcg.leone.ucll.be/extensions/ray-tracers/v5/explanations.html
add_issue "Ray Tracer v6" http://3dcg.leone.ucll.be/extensions/ray-tracers/v6/explanations.html
add_issue "Ray Tracer v7" http://3dcg.leone.ucll.be/extensions/ray-tracers/v7/explanations.html
add_issue "Ray Tracer v8" http://3dcg.leone.ucll.be/extensions/ray-tracers/v8/explanations.html
add_issue "Cartoon Renderer" http://3dcg.leone.ucll.be/extensions/renderers/cartoon/explanations.html
add_issue "Edge Renderer" http://3dcg.leone.ucll.be/extensions/renderers/edge/explanations.html
add_issue "Masking Renderer" http://3dcg.leone.ucll.be/extensions/renderers/masking/explanations.html
add_issue "Multijittered Sampler" http://3dcg.leone.ucll.be/extensions/samplers/multijittered/explanations.html
add_issue "N-Rooks Sampler" http://3dcg.leone.ucll.be/extensions/samplers/nrooks/explanations.html
add_issue "Random Sampler" http://3dcg.leone.ucll.be/extensions/samplers/random/explanations.html
add_issue "Stratified Sampler" http://3dcg.leone.ucll.be/extensions/samplers/stratified/explanations.html
add_issue "Stratified - Half Jittered Sampler" http://3dcg.leone.ucll.be/extensions/samplers/stratified-half-jittered/explanations.html
add_issue "Stratified - Jittered Sampler" http://3dcg.leone.ucll.be/extensions/samplers/stratified-jittered/explanations.html
