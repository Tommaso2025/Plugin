#include <ros/ros.h>
#include <moveit/kinematics_base/kinematics_base.h>
#include <geometry_msgs/Pose.h>
#include <moveit_msgs/MoveItErrorCodes.h>
#include <pluginlib/class_loader.h>
#include <boost/shared_ptr.hpp>
#include <functional> 
#include <kdl_kinematics_plugin/kdl_kinematics_plugin.h>

bool solutionCallback(const geometry_msgs::Pose& ik_pose, const std::vector<double>& solution, moveit_msgs::MoveItErrorCodes& error_code) {
  // Process the solution (this is a placeholder for your actual processing code)
  std::cout << "Found IK solution: ";
  for (const auto& joint_value : solution){
     std::cout << joint_value << " ";
  }
  std::cout << std::endl;
  
  // Process the IK pose if needed
  std::cout << "IK Pose: " << ik_pose << std::endl;
  
  // Set error_code if needed
  error_code.val = moveit_msgs::MoveItErrorCodes::SUCCESS;

  return true;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "load_ik");
  ros::NodeHandle node_obj;
  
  pluginlib::ClassLoader<kinematics::KinematicsBase> load_ik("kdl_kinematics_plugin", "kdl_kinematics_plugin::KDLKinematicsPlugin");

  try{
    // Desired end-effector pose
    geometry_msgs::Pose target_pose;
    target_pose.position.x = 0.5;
    target_pose.position.y = 0.2;
    target_pose.position.z = 0.3;
    target_pose.orientation.w = 1.0;
    target_pose.orientation.x = 0.0;
    target_pose.orientation.y = 0.0;
    target_pose.orientation.z = 0.0;
  
    // Initial seed state for the IK solver
    std::vector<double> seed_state = {0.1, -0.1, 0.2, -0.3, 0.4, -0.5, 0.6};

    // Consistency limits for each joint
    std::vector<double> consistency_limits = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

    // Solution vector
    std::vector<double> solution;

    // Error code
    moveit_msgs::MoveItErrorCodes error_code;

    // Options (assuming default options here)
    kinematics::KinematicsQueryOptions options;
    
    // Dynamically load the custom IK solver plugin
    boost::shared_ptr<kinematics::KinematicsBase> ik_sol = load_ik.createInstance("kdl_kinematics_plugin::KDLKinematicsPlugin");
    //ROS_INFO("Successfully loaded custom IK solver plugin.");
        
    //Dinamically load the custom IK solver
    //boost::shared_ptr<ikinematic_plugin::iKinematicPlugin> ik_sol = ik_loader.createInstance("ik_solver_plugin::iKinematicPlugin");
    
    // Create an instance of the callback function
    kdl_kinematics_plugin::KDLKinematicsPlugin::IKCallbackFn callback_fn = solutionCallback;
    
    // Perform the IK search
    bool success = ik_sol -> searchPositionIK(target_pose, seed_state, 5.0, consistency_limits, solution, callback_fn, error_code, options);
    if (success) {
      ROS_INFO("IK solver succeeded.");
    } else {
      ROS_ERROR("IK solver failed.");
    }
    std::cout << "Solution: ";
    for (const auto& val : solution) {
         std::cout << val << " ";
    }
    std::cout << std::endl;
  
  }
  catch (pluginlib::PluginlibException& ex) {
    ROS_ERROR("The plugin failed to load. Error: %s", ex.what());
  }
  return 0;
}
