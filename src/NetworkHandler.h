//
// Created by Motoki Nakajima on 11/16/25.
//

#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/DoubleTopic.h>
#include <networktables/StructArrayTopic.h>
#include <networktables/StructTopic.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation3d.h>
#include <frc/geometry/Rotation3d.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <string>
#include <vector>
#include <map>

class NetworkHandler {
public:
    NetworkHandler();
    explicit NetworkHandler(const std::string &ipAddress);

    void init(const std::string &ipAddress);

    // Double subscribers
    void addDoubleSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    double getDouble(const std::string &name, double defaultValue = 0.0);

    // Pose2d subscribers
    void addPose2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::Pose2d getPose2d(const std::string &name);

    // Translation2d subscribers
    void addTranslation2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::Translation2d getTranslation2d(const std::string &name);

    // Rotation2d subscribers
    void addRotation2dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::Rotation2d getRotation2d(const std::string &name);

    // Translation3d subscribers
    void addTranslation3dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::Translation3d getTranslation3d(const std::string &name);

    // Rotation3d subscribers
    void addRotation3dSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::Rotation3d getRotation3d(const std::string &name);

    // SwerveModuleState subscribers
    void addSwerveModuleStateSubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    frc::SwerveModuleState getSwerveModuleState(const std::string &name);

    // SwerveModuleState array subscribers
    void addSwerveModuleStateArraySubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    std::vector<frc::SwerveModuleState> getSwerveModuleStateArray(const std::string &name);

    // Pose2d array subscribers (for vision, etc.)
    void addPose2dArraySubscriber(const std::string &name, const std::string &tableName, const std::string &topicName);
    std::vector<frc::Pose2d> getPose2dArray(const std::string &name);

    // Check if subscriber exists
    bool hasSubscriber(const std::string &name) const;

private:
    nt::NetworkTableInstance inst;

    // Subscribers organized by type
    std::map<std::string, nt::DoubleSubscriber> doubleSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::Pose2d>> pose2dSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::Translation2d>> translation2dSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::Rotation2d>> rotation2dSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::Translation3d>> translation3dSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::Rotation3d>> rotation3dSubscribers;
    std::map<std::string, nt::StructSubscriber<frc::SwerveModuleState>> swerveStateSubscribers;
    std::map<std::string, nt::StructArraySubscriber<frc::SwerveModuleState>> swerveStateArraySubscribers;
    std::map<std::string, nt::StructArraySubscriber<frc::Pose2d>> pose2dArraySubscribers;
};

#endif //NETWORKHANDLER_H