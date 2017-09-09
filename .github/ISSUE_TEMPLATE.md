<!-- You can erase any parts of this template not applicable to your Issue. -->

## Bug report

Please replace this line with a brief summary of your issue **AND** if reporting a build issue include relevant terminal output.

#### Context

[this project is split into many parts, what part of the project contains the bug? Examples: Vision, Arduino Controller...] 

#### Process

[in an ordered list explain the process to finding and recreating the issue, example below]

1. User goes to delete a dataset (to save space or whatever)
2. User gets popup modal warning
3. User deletes and it's lost forever

#### Expected result

[describe what you would expect to have resulted from this process]

#### Current result

[describe what you currently experience from this process, and thereby explain the bug]

#### Possible Fix

[not obligatory, but suggest fixes or reasons for the bug]

* Modal tells the user what dataset is being deleted, like “You are about to delete this dataset: car_crashes_2014.”
* A temporary "Trashcan" where you can recover a just deleted dataset if you mess up (maybe it's only good for a few hours, and then it cleans the cache assuming you made the right decision).


## New feature request

[We will consider your request but it may be closed if it's something we're not actively planning to work on.]

Please replace this line with a summary of your suggested feature.

#### Requirements

[explain the concrete changes to the project needed for your feature, example below]

- [ ] Add a "Delete" button to the dataset management page.
- [ ] **Non concrete change:** Create system for showing messages to user.
- [ ] Add delete function to dataset interface.

#### Other thoughts

[explain any other ideas or thoughts you have about this feature.]
